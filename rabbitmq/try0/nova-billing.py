#!/usr/bin/python
import inspect
import os

import eventlet
import greenlet

from nova import context
from nova import db
from nova import exception
from nova import flags
from nova import log as logging
from nova import rpc
from nova import utils
from nova import version
from nova import wsgi

from nova.rpc import impl_kombu
import kombu
import kombu.entity
import kombu.messaging
import kombu.connection

FLAGS = flags.FLAGS
FLAGS.control_exchange = "mynova"

class MyTopicConsumer(impl_kombu.ConsumerBase):
    """Consumer class for 'topic'"""

    def __init__(self, channel, topic, callback, tag, **kwargs):
        """Init a 'topic' queue.

        'channel' is the amqp channel to use
        'topic' is the topic to listen on
        'callback' is the callback to call when messages are received
        'tag' is a unique ID for the consumer on the channel

        Other kombu options may be passed
        """
        # Default options
        options = {'durable': FLAGS.rabbit_durable_queues,
                'auto_delete': False,
                'exclusive': False}
        options.update(kwargs)
        exchange = kombu.entity.Exchange(
                name=FLAGS.control_exchange,
                type='topic',
                durable=options['durable'],
                auto_delete=options['auto_delete'])
        super(MyTopicConsumer, self).__init__(
                channel,
                callback,
                tag,
                name="my" + topic,
                exchange=exchange,
                routing_key=topic,
                **options)


class Listener(object):
    def __init__(self):
        self.params = dict(hostname=FLAGS.rabbit_host,
                          port=FLAGS.rabbit_port,
                          userid=FLAGS.rabbit_userid,
                          password=FLAGS.rabbit_password,
                          virtual_host=FLAGS.rabbit_virtual_host)
        
        print self.params
        self.connection = kombu.connection.BrokerConnection(**self.params)
        self.topic = "nova"
        self.channel = self.connection.channel()
        self.consumers = []
        self.declare_topic_consumer(self.topic, self)
        self.consumer_thread = None
        print "created"

    def declare_consumer(self, consumer_cls, topic, callback):
        """Create a Consumer using the class that was passed in and
        add it to our list of consumers
        """
        consumer = consumer_cls(self.channel, topic, callback,
                10)
        self.consumers.append(consumer)
        return consumer


    def declare_topic_consumer(self, topic, callback=None):
        """Create a 'topic' consumer."""
        self.declare_consumer(MyTopicConsumer, topic, callback)

    def __call__(self, *args, **kwargs):
        print "called: %s %s" %(args, kwargs)

    def __getattr__(self, key):
        print "get %s" % key
        return self

    def consume(self, limit=None):
        """Consume from all queues/consumers"""
        while True:
            print "consume"
            for cons in  self.consumers:
                cons.consume(nowait=True)

    def consume_in_thread(self):
        """Consumer from all queues/consumers in a greenthread"""
        def _consumer_thread():
            try:
                self.consume()
            except greenlet.GreenletExit:
                return
        if self.consumer_thread is None:
            self.consumer_thread = eventlet.spawn(_consumer_thread)
        return self.consumer_thread

    def consume(self):
        self.consume_in_thread()


def main():
    Listener().consume()
    eventlet.sleep(100000)

if __name__ == "__main__":
    main()

