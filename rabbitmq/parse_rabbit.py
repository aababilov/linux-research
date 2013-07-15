#!/usr/bin/python

import time

def get_date_str():
    return time.strftime("%a %b %d %H:%M:%S %Z %Y")

def get_inst_descr(action, payload):
    descr = "%s %s" % (get_date_str(), action)
    for attr in ("instance_id", "project_id", "user_id", "instance_type"):
        descr += " %s=%s" % (attr, payload.get(attr, "None"))
    print descr

def log_inst_info(inst_info):
    if inst_info.get("event_type", None) == "compute.instance.create":
        payload = inst_info.get("payload", {})
        get_inst_descr("created", payload)
    elif inst_info.get("event_type", None) == "compute.instance.delete":
        payload = inst_info.get("payload", {})
        get_inst_descr("deleted", payload)
    elif inst_info.get("method", None) == "run_instance":
        payload = inst_info["args"]["request_spec"]["instance_properties"].copy()
        payload["instance_id"] = inst_info["args"]["instance_id"]
        payload["instance_type"] = inst_info["args"]["request_spec"]["instance_type"]["name"]
        get_inst_descr("run", payload)


run_inst = {u'_context_roles': [u'projectmanager'], u'_context_request_id': u'29615116-ddd0-4a20-8018-ef5f90f8bdf3', u'_context_read_deleted': False, u'args': {u'request_spec': {u'num_instances': 1, u'image': {u'status': u'active', u'name': u'SL61', u'deleted': False, u'container_format': u'ami', u'created_at': u'2011-12-05 12:15:25.541042', u'disk_format': u'ami', u'updated_at': u'2011-12-05 12:15:26.659439', u'properties': {u'kernel_id': u'2', u'owner': None, u'min_ram': u'0', u'ramdisk_id': u'1', u'min_disk': u'0'}, u'location': u'file:///var/lib/glance/images/4', u'checksum': u'ecd1d23a8039b72812db4fee5a11a547', u'is_public': True, u'deleted_at': None, u'id': 4, u'size': 216858624}, u'filter': None, u'instance_type': {u'rxtx_quota': 0, u'flavorid': 2, u'name': u'm1.small', u'deleted': False, u'created_at': None, u'updated_at': None, u'memory_mb': 2048, u'vcpus': 1, u'rxtx_cap': 0, u'extra_specs': {}, u'swap': 0, u'deleted_at': None, u'id': 5, u'local_gb': 20}, u'blob': None, u'instance_properties': {u'vm_state': u'building', u'availability_zone': None, u'ramdisk_id': u'1', u'instance_type_id': 5, u'user_data': u'', u'vm_mode': None, u'reservation_id': u'r-851pambx', u'user_id': u'admin', u'display_description': None, u'key_data': None, u'power_state': 0, u'project_id': u'systenant', u'metadata': {}, u'access_ip_v6': None, u'access_ip_v4': None, u'kernel_id': u'2', u'key_name': None, u'display_name': None, u'config_drive_id': u'', u'local_gb': 20, u'architecture': None, u'locked': False, u'launch_time': u'2011-12-06T19:12:57Z', u'memory_mb': 2048, u'vcpus': 1, u'image_ref': 4, u'root_device_name': None, u'os_type': None, u'config_drive': u''}}, u'requested_networks': None, u'availability_zone': None, u'instance_id': 16, u'admin_password': None, u'injected_files': None}, u'_context_auth_token': None, u'_context_strategy': u'noauth', u'_context_is_admin': True, u'_context_project_id': u'systenant', u'_context_timestamp': u'2011-12-06T19:12:57.805503', u'_context_user_id': u'admin', u'method': u'run_instance', u'_context_remote_address': u'128.107.79.131'}


create_inst =  {u'_context_roles': [], u'_context_request_id': u'520c5e09-d1fa-41bd-8a57-25b4b914d7c3', u'_context_read_deleted': False, u'event_type': u'compute.instance.create', u'timestamp': u'2011-12-06 19:13:01.380354', u'message_id': u'd810d987-a3ee-4d09-bb0c-f6b64bd6ec7c', u'_context_auth_token': None, u'_context_strategy': u'noauth', u'_context_is_admin': True, u'_context_project_id': None, u'_context_timestamp': u'2011-12-06T19:13:01.380373', u'_context_user_id': None, u'_context_remote_address': None, u'publisher_id': u'compute.gm.cloud', u'payload': {u'display_name': u'Server 16', u'created_at': u'2011-12-06 19:12:57', u'instance_type_id': 5, u'instance_id': 16, u'instance_type': u'm1.small', u'image_ref': u'4', u'user_id': u'admin', u'project_id': u'systenant', u'launched_at': u''}, u'priority': u'INFO'}

term_inst = {u'_context_roles': [u'projectmanager'], u'_context_request_id': u'0820c1e1-2063-4a1c-8178-a2f228445ee2', u'_context_read_deleted': False, u'args': {u'instance_id': 24}, u'_context_auth_token': None, u'_context_strategy': u'noauth', u'_context_is_admin': True, u'_context_project_id': u'systenant', u'_context_timestamp': u'2011-12-06T20:14:48.165619', u'_context_user_id': u'admin', u'method': u'terminate_instance', u'_context_remote_address': u'128.107.79.131'}                                                                                                                                         


log_inst_info(create_inst)
log_inst_info(run_inst)
