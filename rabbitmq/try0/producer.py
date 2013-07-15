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
FLAGS.control_exchange = "nova"

class Producer(object):
    def __init__(self):
        self.params = dict(hostname=FLAGS.rabbit_host,
                          port=FLAGS.rabbit_port,
                          userid=FLAGS.rabbit_userid,
                          password=FLAGS.rabbit_password,
                          virtual_host=FLAGS.rabbit_virtual_host)
        
        print self.params
        self.connection = kombu.connection.BrokerConnection(**self.params)
        self.topic = "nova"
        options = {'durable': FLAGS.rabbit_durable_queues,
                'auto_delete': False,
                'exclusive': False}
        exchange = kombu.entity.Exchange(
                name=FLAGS.control_exchange,
                type='topic',
                durable=options['durable'],
                auto_delete=options['auto_delete'])

        self.channel = self.connection.channel()
        prod = kombu.messaging.Producer(self.channel, exchange, routing_key="nova")
        print "created"
        prod.publish(body="hello", routing_key="nova")
    

def main():
    Producer()

if __name__ == "__main__":
    main()

