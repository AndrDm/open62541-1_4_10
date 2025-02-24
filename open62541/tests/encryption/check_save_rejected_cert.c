/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2022 (c) Robert Mak, KEBA 
 */

#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/securitypolicy.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <open62541/plugin/pki_default.h>

#include "client/ua_client_internal.h"
#include "ua_server_internal.h"

#include <stdio.h>
#include <stdlib.h>

#include "certificates.h"
#include "check.h"
#include "testing_clock.h"
#include "testing_networklayers.h"
#include "thread_wrapper.h"

UA_Server *server;
UA_Boolean running;
THREAD_HANDLE server_thread;

THREAD_CALLBACK(serverloop) {
    while(running)
        UA_Server_run_iterate(server, true);
    return 0;
}

/* Generated with create_self-signed.py, with
  -subj "/C=DE/L=Here/O=open62541/CN=open62541Client@localhost"\ */
const size_t clientCertificatePemSize = 1456;
UA_Byte clientCertificatePem[] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x43, 0x45, 0x52,
    0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a,
    0x4d, 0x49, 0x49, 0x45, 0x42, 0x6a, 0x43, 0x43, 0x41, 0x75, 0x36, 0x67, 0x41, 0x77,
    0x49, 0x42, 0x41, 0x67, 0x49, 0x55, 0x41, 0x70, 0x49, 0x71, 0x49, 0x43, 0x47, 0x67,
    0x7a, 0x76, 0x48, 0x77, 0x31, 0x47, 0x52, 0x64, 0x52, 0x4d, 0x50, 0x4e, 0x69, 0x6a,
    0x70, 0x53, 0x51, 0x33, 0x63, 0x77, 0x44, 0x51, 0x59, 0x4a, 0x4b, 0x6f, 0x5a, 0x49,
    0x68, 0x76, 0x63, 0x4e, 0x41, 0x51, 0x45, 0x4c, 0x0a, 0x42, 0x51, 0x41, 0x77, 0x56,
    0x44, 0x45, 0x4c, 0x4d, 0x41, 0x6b, 0x47, 0x41, 0x31, 0x55, 0x45, 0x42, 0x68, 0x4d,
    0x43, 0x52, 0x45, 0x55, 0x78, 0x44, 0x54, 0x41, 0x4c, 0x42, 0x67, 0x4e, 0x56, 0x42,
    0x41, 0x63, 0x4d, 0x42, 0x45, 0x68, 0x6c, 0x63, 0x6d, 0x55, 0x78, 0x45, 0x6a, 0x41,
    0x51, 0x42, 0x67, 0x4e, 0x56, 0x42, 0x41, 0x6f, 0x4d, 0x43, 0x57, 0x39, 0x77, 0x5a,
    0x57, 0x34, 0x32, 0x0a, 0x4d, 0x6a, 0x55, 0x30, 0x4d, 0x54, 0x45, 0x69, 0x4d, 0x43,
    0x41, 0x47, 0x41, 0x31, 0x55, 0x45, 0x41, 0x77, 0x77, 0x5a, 0x62, 0x33, 0x42, 0x6c,
    0x62, 0x6a, 0x59, 0x79, 0x4e, 0x54, 0x51, 0x78, 0x51, 0x32, 0x78, 0x70, 0x5a, 0x57,
    0x35, 0x30, 0x51, 0x47, 0x78, 0x76, 0x59, 0x32, 0x46, 0x73, 0x61, 0x47, 0x39, 0x7a,
    0x64, 0x44, 0x41, 0x65, 0x46, 0x77, 0x30, 0x79, 0x4d, 0x6a, 0x41, 0x34, 0x0a, 0x4d,
    0x54, 0x41, 0x78, 0x4d, 0x54, 0x55, 0x32, 0x4e, 0x44, 0x64, 0x61, 0x46, 0x77, 0x30,
    0x79, 0x4d, 0x7a, 0x41, 0x34, 0x4d, 0x54, 0x41, 0x78, 0x4d, 0x54, 0x55, 0x32, 0x4e,
    0x44, 0x64, 0x61, 0x4d, 0x46, 0x51, 0x78, 0x43, 0x7a, 0x41, 0x4a, 0x42, 0x67, 0x4e,
    0x56, 0x42, 0x41, 0x59, 0x54, 0x41, 0x6b, 0x52, 0x46, 0x4d, 0x51, 0x30, 0x77, 0x43,
    0x77, 0x59, 0x44, 0x56, 0x51, 0x51, 0x48, 0x0a, 0x44, 0x41, 0x52, 0x49, 0x5a, 0x58,
    0x4a, 0x6c, 0x4d, 0x52, 0x49, 0x77, 0x45, 0x41, 0x59, 0x44, 0x56, 0x51, 0x51, 0x4b,
    0x44, 0x41, 0x6c, 0x76, 0x63, 0x47, 0x56, 0x75, 0x4e, 0x6a, 0x49, 0x31, 0x4e, 0x44,
    0x45, 0x78, 0x49, 0x6a, 0x41, 0x67, 0x42, 0x67, 0x4e, 0x56, 0x42, 0x41, 0x4d, 0x4d,
    0x47, 0x57, 0x39, 0x77, 0x5a, 0x57, 0x34, 0x32, 0x4d, 0x6a, 0x55, 0x30, 0x4d, 0x55,
    0x4e, 0x73, 0x0a, 0x61, 0x57, 0x56, 0x75, 0x64, 0x45, 0x42, 0x73, 0x62, 0x32, 0x4e,
    0x68, 0x62, 0x47, 0x68, 0x76, 0x63, 0x33, 0x51, 0x77, 0x67, 0x67, 0x45, 0x69, 0x4d,
    0x41, 0x30, 0x47, 0x43, 0x53, 0x71, 0x47, 0x53, 0x49, 0x62, 0x33, 0x44, 0x51, 0x45,
    0x42, 0x41, 0x51, 0x55, 0x41, 0x41, 0x34, 0x49, 0x42, 0x44, 0x77, 0x41, 0x77, 0x67,
    0x67, 0x45, 0x4b, 0x41, 0x6f, 0x49, 0x42, 0x41, 0x51, 0x43, 0x34, 0x0a, 0x73, 0x56,
    0x61, 0x59, 0x4a, 0x42, 0x57, 0x73, 0x76, 0x36, 0x55, 0x4b, 0x4f, 0x74, 0x55, 0x57,
    0x37, 0x4e, 0x51, 0x6d, 0x7a, 0x44, 0x78, 0x53, 0x43, 0x73, 0x35, 0x6a, 0x6e, 0x6f,
    0x4c, 0x6a, 0x6c, 0x76, 0x4d, 0x76, 0x42, 0x38, 0x52, 0x67, 0x42, 0x4d, 0x5a, 0x2b,
    0x4c, 0x38, 0x34, 0x43, 0x71, 0x68, 0x32, 0x62, 0x47, 0x76, 0x66, 0x4b, 0x54, 0x77,
    0x46, 0x75, 0x5a, 0x78, 0x73, 0x56, 0x0a, 0x58, 0x69, 0x4d, 0x31, 0x71, 0x69, 0x73,
    0x30, 0x44, 0x2b, 0x52, 0x73, 0x4a, 0x32, 0x77, 0x37, 0x4e, 0x72, 0x67, 0x37, 0x56,
    0x7a, 0x4a, 0x6c, 0x56, 0x58, 0x55, 0x67, 0x57, 0x50, 0x38, 0x4f, 0x34, 0x33, 0x48,
    0x65, 0x54, 0x35, 0x36, 0x38, 0x66, 0x31, 0x6f, 0x4d, 0x2f, 0x30, 0x54, 0x4e, 0x52,
    0x4d, 0x47, 0x6e, 0x4b, 0x51, 0x57, 0x52, 0x43, 0x38, 0x63, 0x36, 0x6e, 0x2f, 0x76,
    0x38, 0x0a, 0x41, 0x4f, 0x52, 0x6c, 0x53, 0x46, 0x77, 0x73, 0x33, 0x6e, 0x45, 0x34,
    0x4b, 0x72, 0x48, 0x69, 0x61, 0x47, 0x68, 0x6e, 0x63, 0x68, 0x4b, 0x38, 0x38, 0x32,
    0x70, 0x6a, 0x43, 0x32, 0x71, 0x64, 0x37, 0x59, 0x78, 0x37, 0x6d, 0x61, 0x6e, 0x76,
    0x6c, 0x45, 0x45, 0x4f, 0x73, 0x69, 0x41, 0x30, 0x36, 0x68, 0x4e, 0x36, 0x49, 0x34,
    0x2b, 0x34, 0x4d, 0x54, 0x72, 0x4f, 0x6f, 0x4a, 0x65, 0x77, 0x0a, 0x70, 0x51, 0x36,
    0x45, 0x53, 0x32, 0x42, 0x62, 0x43, 0x67, 0x66, 0x30, 0x4f, 0x67, 0x68, 0x34, 0x37,
    0x54, 0x39, 0x77, 0x64, 0x6b, 0x41, 0x75, 0x51, 0x35, 0x62, 0x47, 0x73, 0x36, 0x6d,
    0x36, 0x47, 0x68, 0x58, 0x5a, 0x58, 0x35, 0x56, 0x78, 0x41, 0x47, 0x6e, 0x6b, 0x70,
    0x59, 0x7a, 0x75, 0x61, 0x6f, 0x64, 0x66, 0x52, 0x6e, 0x4d, 0x62, 0x4f, 0x58, 0x78,
    0x34, 0x32, 0x62, 0x4d, 0x47, 0x0a, 0x65, 0x31, 0x64, 0x41, 0x35, 0x42, 0x4f, 0x62,
    0x6c, 0x49, 0x52, 0x4e, 0x5a, 0x4e, 0x56, 0x77, 0x2b, 0x77, 0x33, 0x34, 0x4e, 0x4c,
    0x55, 0x63, 0x75, 0x47, 0x52, 0x41, 0x4a, 0x69, 0x34, 0x43, 0x45, 0x77, 0x6c, 0x52,
    0x4f, 0x4f, 0x59, 0x5a, 0x51, 0x77, 0x68, 0x6a, 0x4d, 0x32, 0x69, 0x47, 0x73, 0x48,
    0x77, 0x61, 0x4c, 0x53, 0x6b, 0x44, 0x50, 0x76, 0x30, 0x42, 0x6d, 0x44, 0x79, 0x67,
    0x0a, 0x69, 0x6f, 0x46, 0x48, 0x38, 0x67, 0x7a, 0x63, 0x61, 0x38, 0x72, 0x5a, 0x36,
    0x32, 0x30, 0x70, 0x4e, 0x50, 0x5a, 0x4c, 0x41, 0x67, 0x4d, 0x42, 0x41, 0x41, 0x47,
    0x6a, 0x67, 0x63, 0x38, 0x77, 0x67, 0x63, 0x77, 0x77, 0x48, 0x51, 0x59, 0x44, 0x56,
    0x52, 0x30, 0x4f, 0x42, 0x42, 0x59, 0x45, 0x46, 0x48, 0x38, 0x66, 0x52, 0x32, 0x6a,
    0x47, 0x56, 0x56, 0x39, 0x56, 0x38, 0x68, 0x41, 0x2f, 0x0a, 0x77, 0x41, 0x57, 0x59,
    0x36, 0x78, 0x74, 0x4f, 0x39, 0x57, 0x4f, 0x41, 0x4d, 0x42, 0x38, 0x47, 0x41, 0x31,
    0x55, 0x64, 0x49, 0x77, 0x51, 0x59, 0x4d, 0x42, 0x61, 0x41, 0x46, 0x48, 0x38, 0x66,
    0x52, 0x32, 0x6a, 0x47, 0x56, 0x56, 0x39, 0x56, 0x38, 0x68, 0x41, 0x2f, 0x77, 0x41,
    0x57, 0x59, 0x36, 0x78, 0x74, 0x4f, 0x39, 0x57, 0x4f, 0x41, 0x4d, 0x41, 0x6b, 0x47,
    0x41, 0x31, 0x55, 0x64, 0x0a, 0x45, 0x77, 0x51, 0x43, 0x4d, 0x41, 0x41, 0x77, 0x43,
    0x77, 0x59, 0x44, 0x56, 0x52, 0x30, 0x50, 0x42, 0x41, 0x51, 0x44, 0x41, 0x67, 0x4c,
    0x30, 0x4d, 0x42, 0x30, 0x47, 0x41, 0x31, 0x55, 0x64, 0x4a, 0x51, 0x51, 0x57, 0x4d,
    0x42, 0x51, 0x47, 0x43, 0x43, 0x73, 0x47, 0x41, 0x51, 0x55, 0x46, 0x42, 0x77, 0x4d,
    0x42, 0x42, 0x67, 0x67, 0x72, 0x42, 0x67, 0x45, 0x46, 0x42, 0x51, 0x63, 0x44, 0x0a,
    0x41, 0x6a, 0x42, 0x54, 0x42, 0x67, 0x4e, 0x56, 0x48, 0x52, 0x45, 0x45, 0x54, 0x44,
    0x42, 0x4b, 0x67, 0x67, 0x78, 0x6c, 0x59, 0x57, 0x4e, 0x6d, 0x4d, 0x44, 0x56, 0x68,
    0x5a, 0x44, 0x4a, 0x6b, 0x5a, 0x47, 0x57, 0x43, 0x44, 0x47, 0x56, 0x68, 0x59, 0x32,
    0x59, 0x77, 0x4e, 0x57, 0x46, 0x6b, 0x4d, 0x6d, 0x52, 0x6b, 0x5a, 0x59, 0x63, 0x45,
    0x72, 0x42, 0x45, 0x41, 0x41, 0x6f, 0x63, 0x45, 0x0a, 0x66, 0x77, 0x41, 0x41, 0x41,
    0x59, 0x59, 0x67, 0x64, 0x58, 0x4a, 0x75, 0x4f, 0x6d, 0x39, 0x77, 0x5a, 0x57, 0x34,
    0x32, 0x4d, 0x6a, 0x55, 0x30, 0x4d, 0x53, 0x35, 0x7a, 0x5a, 0x58, 0x4a, 0x32, 0x5a,
    0x58, 0x49, 0x75, 0x59, 0x58, 0x42, 0x77, 0x62, 0x47, 0x6c, 0x6a, 0x59, 0x58, 0x52,
    0x70, 0x62, 0x32, 0x34, 0x77, 0x44, 0x51, 0x59, 0x4a, 0x4b, 0x6f, 0x5a, 0x49, 0x68,
    0x76, 0x63, 0x4e, 0x0a, 0x41, 0x51, 0x45, 0x4c, 0x42, 0x51, 0x41, 0x44, 0x67, 0x67,
    0x45, 0x42, 0x41, 0x42, 0x39, 0x30, 0x52, 0x68, 0x4c, 0x39, 0x43, 0x46, 0x6b, 0x69,
    0x52, 0x32, 0x4a, 0x37, 0x33, 0x50, 0x58, 0x6b, 0x36, 0x7a, 0x65, 0x79, 0x73, 0x57,
    0x4f, 0x6f, 0x59, 0x4f, 0x63, 0x73, 0x57, 0x44, 0x67, 0x79, 0x62, 0x65, 0x55, 0x5a,
    0x68, 0x78, 0x41, 0x71, 0x37, 0x58, 0x46, 0x42, 0x42, 0x53, 0x58, 0x42, 0x0a, 0x66,
    0x4e, 0x78, 0x4a, 0x76, 0x55, 0x58, 0x6d, 0x43, 0x62, 0x6f, 0x72, 0x42, 0x53, 0x4b,
    0x58, 0x65, 0x44, 0x52, 0x5a, 0x4a, 0x4a, 0x4a, 0x52, 0x73, 0x59, 0x37, 0x5a, 0x53,
    0x53, 0x57, 0x76, 0x48, 0x5a, 0x4f, 0x78, 0x79, 0x62, 0x33, 0x5a, 0x43, 0x71, 0x69,
    0x4f, 0x36, 0x70, 0x57, 0x78, 0x33, 0x44, 0x41, 0x58, 0x30, 0x2b, 0x31, 0x57, 0x69,
    0x4c, 0x4d, 0x75, 0x54, 0x31, 0x39, 0x68, 0x0a, 0x52, 0x7a, 0x54, 0x67, 0x67, 0x32,
    0x30, 0x43, 0x2b, 0x75, 0x36, 0x4f, 0x43, 0x66, 0x64, 0x71, 0x41, 0x65, 0x32, 0x4a,
    0x2b, 0x55, 0x2b, 0x4f, 0x36, 0x6c, 0x6a, 0x44, 0x35, 0x69, 0x4a, 0x4d, 0x56, 0x4f,
    0x61, 0x71, 0x4c, 0x79, 0x4f, 0x39, 0x4b, 0x62, 0x72, 0x62, 0x46, 0x59, 0x49, 0x44,
    0x44, 0x6f, 0x75, 0x31, 0x77, 0x54, 0x55, 0x49, 0x4c, 0x78, 0x52, 0x59, 0x61, 0x31,
    0x32, 0x6c, 0x0a, 0x70, 0x45, 0x71, 0x50, 0x6a, 0x2b, 0x63, 0x34, 0x49, 0x68, 0x42,
    0x2f, 0x52, 0x6a, 0x42, 0x56, 0x41, 0x75, 0x37, 0x7a, 0x4f, 0x49, 0x64, 0x34, 0x59,
    0x52, 0x5a, 0x33, 0x51, 0x48, 0x71, 0x71, 0x56, 0x50, 0x66, 0x4e, 0x2b, 0x55, 0x58,
    0x54, 0x46, 0x78, 0x55, 0x46, 0x38, 0x69, 0x68, 0x55, 0x2b, 0x4b, 0x42, 0x52, 0x6a,
    0x77, 0x4e, 0x71, 0x68, 0x6a, 0x74, 0x6e, 0x5a, 0x53, 0x62, 0x49, 0x0a, 0x5a, 0x6b,
    0x34, 0x52, 0x55, 0x42, 0x70, 0x56, 0x2f, 0x38, 0x4b, 0x59, 0x54, 0x42, 0x70, 0x56,
    0x72, 0x42, 0x61, 0x7a, 0x47, 0x43, 0x6d, 0x43, 0x64, 0x78, 0x6b, 0x32, 0x58, 0x6d,
    0x53, 0x6a, 0x47, 0x36, 0x6a, 0x68, 0x73, 0x4d, 0x61, 0x70, 0x77, 0x78, 0x79, 0x4b,
    0x59, 0x34, 0x42, 0x45, 0x79, 0x6f, 0x39, 0x4f, 0x32, 0x53, 0x6d, 0x59, 0x78, 0x69,
    0x45, 0x48, 0x73, 0x59, 0x47, 0x76, 0x0a, 0x39, 0x61, 0x62, 0x33, 0x41, 0x75, 0x6e,
    0x38, 0x53, 0x70, 0x51, 0x72, 0x6b, 0x55, 0x37, 0x44, 0x4f, 0x72, 0x45, 0x42, 0x31,
    0x44, 0x69, 0x37, 0x6b, 0x36, 0x49, 0x67, 0x65, 0x4c, 0x53, 0x73, 0x76, 0x4f, 0x77,
    0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e, 0x44, 0x20, 0x43, 0x45, 0x52,
    0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a};

UA_Byte clientCertificateThumbprint[] = "4D11B79D8100DCE2B19918A0FDACD24727FE99DE";

UA_Byte clientCertificateKey[] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x52, 0x53, 0x41,
    0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d,
    0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x45, 0x6f, 0x77, 0x49, 0x42, 0x41, 0x41,
    0x4b, 0x43, 0x41, 0x51, 0x45, 0x41, 0x75, 0x4c, 0x46, 0x57, 0x6d, 0x43, 0x51, 0x56,
    0x72, 0x4c, 0x2b, 0x6c, 0x43, 0x6a, 0x72, 0x56, 0x46, 0x75, 0x7a, 0x55, 0x4a, 0x73,
    0x77, 0x38, 0x55, 0x67, 0x72, 0x4f, 0x59, 0x35, 0x36, 0x43, 0x34, 0x35, 0x62, 0x7a,
    0x4c, 0x77, 0x66, 0x45, 0x59, 0x41, 0x54, 0x47, 0x66, 0x69, 0x2f, 0x4f, 0x0a, 0x41,
    0x71, 0x6f, 0x64, 0x6d, 0x78, 0x72, 0x33, 0x79, 0x6b, 0x38, 0x42, 0x62, 0x6d, 0x63,
    0x62, 0x46, 0x56, 0x34, 0x6a, 0x4e, 0x61, 0x6f, 0x72, 0x4e, 0x41, 0x2f, 0x6b, 0x62,
    0x43, 0x64, 0x73, 0x4f, 0x7a, 0x61, 0x34, 0x4f, 0x31, 0x63, 0x79, 0x5a, 0x56, 0x56,
    0x31, 0x49, 0x46, 0x6a, 0x2f, 0x44, 0x75, 0x4e, 0x78, 0x33, 0x6b, 0x2b, 0x65, 0x76,
    0x48, 0x39, 0x61, 0x44, 0x50, 0x39, 0x45, 0x0a, 0x7a, 0x55, 0x54, 0x42, 0x70, 0x79,
    0x6b, 0x46, 0x6b, 0x51, 0x76, 0x48, 0x4f, 0x70, 0x2f, 0x37, 0x2f, 0x41, 0x44, 0x6b,
    0x5a, 0x55, 0x68, 0x63, 0x4c, 0x4e, 0x35, 0x78, 0x4f, 0x43, 0x71, 0x78, 0x34, 0x6d,
    0x68, 0x6f, 0x5a, 0x33, 0x49, 0x53, 0x76, 0x50, 0x4e, 0x71, 0x59, 0x77, 0x74, 0x71,
    0x6e, 0x65, 0x32, 0x4d, 0x65, 0x35, 0x6d, 0x70, 0x37, 0x35, 0x52, 0x42, 0x44, 0x72,
    0x49, 0x67, 0x0a, 0x4e, 0x4f, 0x6f, 0x54, 0x65, 0x69, 0x4f, 0x50, 0x75, 0x44, 0x45,
    0x36, 0x7a, 0x71, 0x43, 0x58, 0x73, 0x4b, 0x55, 0x4f, 0x68, 0x45, 0x74, 0x67, 0x57,
    0x77, 0x6f, 0x48, 0x39, 0x44, 0x6f, 0x49, 0x65, 0x4f, 0x30, 0x2f, 0x63, 0x48, 0x5a,
    0x41, 0x4c, 0x6b, 0x4f, 0x57, 0x78, 0x72, 0x4f, 0x70, 0x75, 0x68, 0x6f, 0x56, 0x32,
    0x56, 0x2b, 0x56, 0x63, 0x51, 0x42, 0x70, 0x35, 0x4b, 0x57, 0x4d, 0x0a, 0x37, 0x6d,
    0x71, 0x48, 0x58, 0x30, 0x5a, 0x7a, 0x47, 0x7a, 0x6c, 0x38, 0x65, 0x4e, 0x6d, 0x7a,
    0x42, 0x6e, 0x74, 0x58, 0x51, 0x4f, 0x51, 0x54, 0x6d, 0x35, 0x53, 0x45, 0x54, 0x57,
    0x54, 0x56, 0x63, 0x50, 0x73, 0x4e, 0x2b, 0x44, 0x53, 0x31, 0x48, 0x4c, 0x68, 0x6b,
    0x51, 0x43, 0x59, 0x75, 0x41, 0x68, 0x4d, 0x4a, 0x55, 0x54, 0x6a, 0x6d, 0x47, 0x55,
    0x4d, 0x49, 0x59, 0x7a, 0x4e, 0x6f, 0x0a, 0x68, 0x72, 0x42, 0x38, 0x47, 0x69, 0x30,
    0x70, 0x41, 0x7a, 0x37, 0x39, 0x41, 0x5a, 0x67, 0x38, 0x6f, 0x49, 0x71, 0x42, 0x52,
    0x2f, 0x49, 0x4d, 0x33, 0x47, 0x76, 0x4b, 0x32, 0x65, 0x74, 0x74, 0x4b, 0x54, 0x54,
    0x32, 0x53, 0x77, 0x49, 0x44, 0x41, 0x51, 0x41, 0x42, 0x41, 0x6f, 0x49, 0x42, 0x41,
    0x45, 0x4d, 0x43, 0x68, 0x4b, 0x71, 0x61, 0x6e, 0x51, 0x71, 0x61, 0x56, 0x65, 0x55,
    0x4b, 0x0a, 0x52, 0x33, 0x6f, 0x54, 0x33, 0x7a, 0x31, 0x63, 0x61, 0x4a, 0x35, 0x54,
    0x73, 0x57, 0x4a, 0x50, 0x68, 0x71, 0x6e, 0x51, 0x67, 0x4e, 0x63, 0x56, 0x65, 0x46,
    0x68, 0x6d, 0x49, 0x79, 0x5a, 0x78, 0x62, 0x63, 0x74, 0x6c, 0x73, 0x57, 0x77, 0x76,
    0x4d, 0x71, 0x78, 0x43, 0x55, 0x67, 0x43, 0x65, 0x68, 0x43, 0x4d, 0x53, 0x6a, 0x71,
    0x2f, 0x50, 0x31, 0x2f, 0x45, 0x42, 0x75, 0x78, 0x7a, 0x4b, 0x0a, 0x69, 0x4f, 0x68,
    0x4c, 0x43, 0x44, 0x6a, 0x76, 0x67, 0x43, 0x64, 0x6f, 0x42, 0x43, 0x45, 0x43, 0x61,
    0x54, 0x67, 0x62, 0x71, 0x5a, 0x72, 0x42, 0x52, 0x4a, 0x53, 0x62, 0x6d, 0x43, 0x36,
    0x54, 0x42, 0x34, 0x46, 0x36, 0x61, 0x74, 0x43, 0x64, 0x66, 0x35, 0x6d, 0x4b, 0x72,
    0x6e, 0x52, 0x45, 0x79, 0x34, 0x59, 0x35, 0x52, 0x4b, 0x54, 0x43, 0x78, 0x6a, 0x36,
    0x35, 0x54, 0x6c, 0x62, 0x55, 0x0a, 0x6c, 0x73, 0x6e, 0x51, 0x6d, 0x2b, 0x43, 0x38,
    0x63, 0x4c, 0x51, 0x42, 0x6c, 0x52, 0x33, 0x75, 0x62, 0x48, 0x5a, 0x30, 0x55, 0x37,
    0x34, 0x63, 0x6d, 0x4a, 0x32, 0x46, 0x6a, 0x4c, 0x6c, 0x59, 0x61, 0x77, 0x74, 0x39,
    0x6f, 0x4c, 0x63, 0x48, 0x35, 0x6f, 0x30, 0x42, 0x58, 0x70, 0x44, 0x79, 0x62, 0x73,
    0x31, 0x4d, 0x69, 0x6e, 0x6e, 0x69, 0x6b, 0x4f, 0x55, 0x35, 0x33, 0x61, 0x48, 0x75,
    0x0a, 0x38, 0x39, 0x6e, 0x2b, 0x69, 0x2b, 0x31, 0x35, 0x6d, 0x76, 0x6a, 0x31, 0x6a,
    0x68, 0x67, 0x6c, 0x59, 0x48, 0x6c, 0x79, 0x31, 0x65, 0x70, 0x69, 0x53, 0x63, 0x50,
    0x50, 0x39, 0x6d, 0x52, 0x6e, 0x41, 0x76, 0x46, 0x32, 0x43, 0x53, 0x2b, 0x64, 0x55,
    0x64, 0x69, 0x73, 0x59, 0x47, 0x78, 0x5a, 0x4a, 0x73, 0x45, 0x51, 0x5a, 0x77, 0x4c,
    0x39, 0x6f, 0x4b, 0x74, 0x6f, 0x58, 0x66, 0x34, 0x65, 0x0a, 0x5a, 0x76, 0x4d, 0x78,
    0x51, 0x70, 0x6f, 0x6b, 0x4c, 0x56, 0x64, 0x74, 0x38, 0x59, 0x6b, 0x4d, 0x6c, 0x36,
    0x42, 0x65, 0x6e, 0x61, 0x34, 0x49, 0x70, 0x45, 0x61, 0x50, 0x31, 0x7a, 0x62, 0x77,
    0x58, 0x76, 0x63, 0x4e, 0x67, 0x31, 0x4d, 0x6a, 0x42, 0x6b, 0x79, 0x39, 0x55, 0x71,
    0x6f, 0x4e, 0x69, 0x6d, 0x41, 0x70, 0x59, 0x7a, 0x56, 0x51, 0x37, 0x7a, 0x71, 0x53,
    0x62, 0x57, 0x62, 0x42, 0x0a, 0x44, 0x46, 0x6c, 0x74, 0x53, 0x6d, 0x45, 0x43, 0x67,
    0x59, 0x45, 0x41, 0x35, 0x58, 0x55, 0x75, 0x79, 0x2f, 0x67, 0x44, 0x6c, 0x56, 0x51,
    0x45, 0x49, 0x41, 0x32, 0x72, 0x74, 0x71, 0x6c, 0x58, 0x57, 0x7a, 0x50, 0x57, 0x6c,
    0x61, 0x6b, 0x42, 0x61, 0x4a, 0x48, 0x31, 0x66, 0x33, 0x62, 0x72, 0x37, 0x39, 0x57,
    0x65, 0x30, 0x4e, 0x51, 0x46, 0x34, 0x59, 0x76, 0x79, 0x4f, 0x7a, 0x39, 0x33, 0x0a,
    0x79, 0x76, 0x6d, 0x58, 0x6b, 0x2b, 0x53, 0x4d, 0x41, 0x76, 0x32, 0x32, 0x6d, 0x6e,
    0x7a, 0x31, 0x69, 0x76, 0x48, 0x74, 0x57, 0x36, 0x54, 0x57, 0x57, 0x61, 0x68, 0x61,
    0x66, 0x34, 0x54, 0x65, 0x44, 0x50, 0x65, 0x61, 0x4b, 0x62, 0x4e, 0x37, 0x66, 0x33,
    0x2f, 0x67, 0x56, 0x71, 0x39, 0x68, 0x46, 0x46, 0x6d, 0x68, 0x79, 0x41, 0x4e, 0x46,
    0x7a, 0x70, 0x47, 0x42, 0x50, 0x6f, 0x68, 0x36, 0x0a, 0x74, 0x52, 0x41, 0x71, 0x44,
    0x36, 0x39, 0x43, 0x50, 0x5a, 0x36, 0x66, 0x47, 0x72, 0x71, 0x59, 0x55, 0x58, 0x59,
    0x72, 0x51, 0x7a, 0x6e, 0x4d, 0x4c, 0x65, 0x73, 0x6c, 0x4c, 0x76, 0x70, 0x34, 0x53,
    0x58, 0x68, 0x52, 0x6e, 0x6e, 0x46, 0x6b, 0x6c, 0x2b, 0x77, 0x61, 0x45, 0x75, 0x43,
    0x45, 0x35, 0x6e, 0x4d, 0x36, 0x31, 0x67, 0x4d, 0x43, 0x67, 0x59, 0x45, 0x41, 0x7a,
    0x67, 0x36, 0x4e, 0x0a, 0x4b, 0x6b, 0x73, 0x6c, 0x79, 0x38, 0x39, 0x42, 0x43, 0x41,
    0x71, 0x36, 0x79, 0x73, 0x2f, 0x62, 0x47, 0x61, 0x61, 0x62, 0x73, 0x32, 0x75, 0x68,
    0x74, 0x46, 0x6b, 0x50, 0x56, 0x61, 0x64, 0x44, 0x2f, 0x2f, 0x4f, 0x54, 0x52, 0x62,
    0x68, 0x36, 0x73, 0x31, 0x43, 0x35, 0x74, 0x74, 0x6e, 0x52, 0x46, 0x57, 0x2b, 0x49,
    0x6b, 0x4b, 0x76, 0x6b, 0x78, 0x6d, 0x4b, 0x37, 0x6c, 0x66, 0x50, 0x4f, 0x0a, 0x56,
    0x53, 0x50, 0x47, 0x64, 0x65, 0x50, 0x57, 0x35, 0x73, 0x4c, 0x69, 0x4b, 0x63, 0x45,
    0x67, 0x74, 0x7a, 0x30, 0x65, 0x64, 0x57, 0x6d, 0x7a, 0x59, 0x74, 0x6f, 0x72, 0x55,
    0x76, 0x4d, 0x4b, 0x30, 0x37, 0x4d, 0x63, 0x31, 0x57, 0x38, 0x76, 0x75, 0x41, 0x38,
    0x79, 0x4a, 0x44, 0x4d, 0x53, 0x50, 0x57, 0x57, 0x77, 0x45, 0x47, 0x32, 0x34, 0x34,
    0x4d, 0x59, 0x4c, 0x77, 0x72, 0x46, 0x66, 0x0a, 0x76, 0x31, 0x35, 0x72, 0x66, 0x4a,
    0x78, 0x61, 0x6c, 0x33, 0x79, 0x2f, 0x63, 0x48, 0x52, 0x4b, 0x33, 0x41, 0x6a, 0x50,
    0x44, 0x34, 0x4b, 0x75, 0x6b, 0x57, 0x4e, 0x31, 0x44, 0x63, 0x53, 0x2f, 0x71, 0x4b,
    0x38, 0x63, 0x73, 0x42, 0x6b, 0x43, 0x67, 0x59, 0x41, 0x4d, 0x43, 0x4a, 0x6f, 0x38,
    0x72, 0x6a, 0x51, 0x5a, 0x35, 0x37, 0x38, 0x54, 0x6f, 0x30, 0x50, 0x6e, 0x48, 0x33,
    0x68, 0x71, 0x0a, 0x57, 0x77, 0x79, 0x63, 0x36, 0x72, 0x45, 0x64, 0x4e, 0x39, 0x4a,
    0x6c, 0x4c, 0x65, 0x70, 0x76, 0x75, 0x49, 0x64, 0x4d, 0x73, 0x6d, 0x48, 0x67, 0x6b,
    0x30, 0x4e, 0x50, 0x34, 0x69, 0x4d, 0x35, 0x4c, 0x4e, 0x2f, 0x4c, 0x4c, 0x4d, 0x67,
    0x2b, 0x2b, 0x2b, 0x6c, 0x51, 0x72, 0x73, 0x37, 0x39, 0x79, 0x33, 0x52, 0x45, 0x51,
    0x78, 0x2f, 0x4f, 0x73, 0x65, 0x71, 0x56, 0x46, 0x33, 0x58, 0x42, 0x0a, 0x76, 0x6c,
    0x61, 0x43, 0x61, 0x31, 0x78, 0x46, 0x73, 0x6f, 0x49, 0x6b, 0x61, 0x61, 0x77, 0x77,
    0x73, 0x67, 0x61, 0x76, 0x41, 0x36, 0x54, 0x73, 0x6b, 0x57, 0x72, 0x79, 0x79, 0x5a,
    0x75, 0x4e, 0x31, 0x56, 0x77, 0x76, 0x57, 0x47, 0x53, 0x6a, 0x38, 0x4b, 0x61, 0x74,
    0x63, 0x79, 0x32, 0x37, 0x7a, 0x2f, 0x4f, 0x79, 0x34, 0x64, 0x77, 0x59, 0x61, 0x47,
    0x57, 0x5a, 0x30, 0x68, 0x37, 0x75, 0x0a, 0x30, 0x33, 0x57, 0x4d, 0x56, 0x71, 0x77,
    0x4d, 0x33, 0x35, 0x2f, 0x36, 0x62, 0x33, 0x58, 0x6f, 0x31, 0x42, 0x41, 0x34, 0x32,
    0x77, 0x4b, 0x42, 0x67, 0x42, 0x58, 0x72, 0x76, 0x6d, 0x44, 0x4e, 0x64, 0x63, 0x76,
    0x6b, 0x31, 0x49, 0x70, 0x43, 0x65, 0x66, 0x53, 0x78, 0x67, 0x43, 0x47, 0x4f, 0x63,
    0x2b, 0x6e, 0x32, 0x66, 0x56, 0x46, 0x75, 0x57, 0x41, 0x39, 0x49, 0x71, 0x42, 0x64,
    0x47, 0x0a, 0x6c, 0x6c, 0x68, 0x49, 0x63, 0x2b, 0x55, 0x33, 0x70, 0x55, 0x6f, 0x71,
    0x69, 0x65, 0x2b, 0x35, 0x32, 0x64, 0x46, 0x71, 0x4f, 0x41, 0x42, 0x53, 0x36, 0x4a,
    0x6e, 0x66, 0x51, 0x67, 0x67, 0x55, 0x73, 0x6a, 0x78, 0x41, 0x62, 0x4e, 0x42, 0x48,
    0x30, 0x7a, 0x2b, 0x56, 0x36, 0x43, 0x45, 0x57, 0x51, 0x33, 0x4e, 0x43, 0x4e, 0x32,
    0x39, 0x41, 0x76, 0x6e, 0x4d, 0x6f, 0x6e, 0x2f, 0x49, 0x39, 0x0a, 0x6a, 0x38, 0x65,
    0x30, 0x2b, 0x47, 0x4b, 0x67, 0x57, 0x7a, 0x6b, 0x32, 0x70, 0x61, 0x34, 0x61, 0x62,
    0x30, 0x79, 0x51, 0x48, 0x36, 0x62, 0x70, 0x36, 0x72, 0x35, 0x66, 0x6d, 0x45, 0x77,
    0x48, 0x67, 0x32, 0x2f, 0x53, 0x51, 0x6d, 0x44, 0x7a, 0x53, 0x48, 0x70, 0x79, 0x4a,
    0x4c, 0x53, 0x62, 0x79, 0x30, 0x74, 0x66, 0x48, 0x36, 0x73, 0x66, 0x35, 0x59, 0x66,
    0x39, 0x63, 0x6c, 0x5a, 0x44, 0x0a, 0x71, 0x73, 0x32, 0x68, 0x41, 0x6f, 0x47, 0x42,
    0x41, 0x4c, 0x53, 0x76, 0x34, 0x49, 0x74, 0x51, 0x38, 0x35, 0x4a, 0x4a, 0x4a, 0x69,
    0x55, 0x36, 0x55, 0x63, 0x32, 0x77, 0x2b, 0x43, 0x42, 0x4e, 0x41, 0x50, 0x4f, 0x63,
    0x4c, 0x33, 0x55, 0x51, 0x51, 0x44, 0x68, 0x70, 0x50, 0x75, 0x7a, 0x4e, 0x33, 0x6c,
    0x7a, 0x74, 0x30, 0x43, 0x64, 0x68, 0x37, 0x78, 0x5a, 0x34, 0x59, 0x6a, 0x69, 0x78,
    0x0a, 0x70, 0x6c, 0x6a, 0x55, 0x4c, 0x51, 0x44, 0x75, 0x41, 0x6d, 0x30, 0x79, 0x62,
    0x6c, 0x59, 0x4c, 0x39, 0x4f, 0x44, 0x39, 0x78, 0x57, 0x38, 0x63, 0x4f, 0x4f, 0x6d,
    0x32, 0x31, 0x71, 0x69, 0x50, 0x71, 0x70, 0x71, 0x46, 0x69, 0x38, 0x32, 0x32, 0x2f,
    0x62, 0x34, 0x4a, 0x78, 0x63, 0x35, 0x32, 0x51, 0x33, 0x52, 0x67, 0x51, 0x33, 0x39,
    0x6e, 0x48, 0x43, 0x62, 0x61, 0x39, 0x4b, 0x69, 0x61, 0x0a, 0x59, 0x66, 0x62, 0x2b,
    0x54, 0x6a, 0x5a, 0x67, 0x61, 0x71, 0x74, 0x6a, 0x5a, 0x4c, 0x32, 0x36, 0x41, 0x46,
    0x4e, 0x6d, 0x65, 0x51, 0x52, 0x74, 0x4b, 0x31, 0x57, 0x50, 0x79, 0x49, 0x56, 0x72,
    0x4a, 0x6e, 0x75, 0x63, 0x71, 0x56, 0x52, 0x4e, 0x75, 0x32, 0x52, 0x71, 0x53, 0x6f,
    0x72, 0x74, 0x79, 0x65, 0x2f, 0x51, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e,
    0x44, 0x20, 0x52, 0x53, 0x41, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20,
    0x4b, 0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a};

#define CLIENT_CERTIFICATE_DER_SIZE 1034
UA_Byte clientCertificateDer[] = {
    0x30, 0x82, 0x04, 0x06, 0x30, 0x82, 0x02, 0xee, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02,
    0x14, 0x02, 0x92, 0x2a, 0x20, 0x21, 0xa0, 0xce, 0xf1, 0xf0, 0xd4, 0x64, 0x5d, 0x44,
    0xc3, 0xcd, 0x8a, 0x3a, 0x52, 0x43, 0x77, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
    0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x54, 0x31, 0x0b, 0x30, 0x09,
    0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x44, 0x45, 0x31, 0x0d, 0x30, 0x0b, 0x06,
    0x03, 0x55, 0x04, 0x07, 0x0c, 0x04, 0x48, 0x65, 0x72, 0x65, 0x31, 0x12, 0x30, 0x10,
    0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c, 0x09, 0x6f, 0x70, 0x65, 0x6e, 0x36, 0x32, 0x35,
    0x34, 0x31, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x19, 0x6f,
    0x70, 0x65, 0x6e, 0x36, 0x32, 0x35, 0x34, 0x31, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74,
    0x40, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x68, 0x6f, 0x73, 0x74, 0x30, 0x1e, 0x17, 0x0d,
    0x32, 0x32, 0x30, 0x38, 0x31, 0x30, 0x31, 0x31, 0x35, 0x36, 0x34, 0x37, 0x5a, 0x17,
    0x0d, 0x32, 0x33, 0x30, 0x38, 0x31, 0x30, 0x31, 0x31, 0x35, 0x36, 0x34, 0x37, 0x5a,
    0x30, 0x54, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x44,
    0x45, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55, 0x04, 0x07, 0x0c, 0x04, 0x48, 0x65,
    0x72, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c, 0x09, 0x6f,
    0x70, 0x65, 0x6e, 0x36, 0x32, 0x35, 0x34, 0x31, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03,
    0x55, 0x04, 0x03, 0x0c, 0x19, 0x6f, 0x70, 0x65, 0x6e, 0x36, 0x32, 0x35, 0x34, 0x31,
    0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x40, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x68, 0x6f,
    0x73, 0x74, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
    0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82,
    0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xb8, 0xb1, 0x56, 0x98, 0x24, 0x15, 0xac,
    0xbf, 0xa5, 0x0a, 0x3a, 0xd5, 0x16, 0xec, 0xd4, 0x26, 0xcc, 0x3c, 0x52, 0x0a, 0xce,
    0x63, 0x9e, 0x82, 0xe3, 0x96, 0xf3, 0x2f, 0x07, 0xc4, 0x60, 0x04, 0xc6, 0x7e, 0x2f,
    0xce, 0x02, 0xaa, 0x1d, 0x9b, 0x1a, 0xf7, 0xca, 0x4f, 0x01, 0x6e, 0x67, 0x1b, 0x15,
    0x5e, 0x23, 0x35, 0xaa, 0x2b, 0x34, 0x0f, 0xe4, 0x6c, 0x27, 0x6c, 0x3b, 0x36, 0xb8,
    0x3b, 0x57, 0x32, 0x65, 0x55, 0x75, 0x20, 0x58, 0xff, 0x0e, 0xe3, 0x71, 0xde, 0x4f,
    0x9e, 0xbc, 0x7f, 0x5a, 0x0c, 0xff, 0x44, 0xcd, 0x44, 0xc1, 0xa7, 0x29, 0x05, 0x91,
    0x0b, 0xc7, 0x3a, 0x9f, 0xfb, 0xfc, 0x00, 0xe4, 0x65, 0x48, 0x5c, 0x2c, 0xde, 0x71,
    0x38, 0x2a, 0xb1, 0xe2, 0x68, 0x68, 0x67, 0x72, 0x12, 0xbc, 0xf3, 0x6a, 0x63, 0x0b,
    0x6a, 0x9d, 0xed, 0x8c, 0x7b, 0x99, 0xa9, 0xef, 0x94, 0x41, 0x0e, 0xb2, 0x20, 0x34,
    0xea, 0x13, 0x7a, 0x23, 0x8f, 0xb8, 0x31, 0x3a, 0xce, 0xa0, 0x97, 0xb0, 0xa5, 0x0e,
    0x84, 0x4b, 0x60, 0x5b, 0x0a, 0x07, 0xf4, 0x3a, 0x08, 0x78, 0xed, 0x3f, 0x70, 0x76,
    0x40, 0x2e, 0x43, 0x96, 0xc6, 0xb3, 0xa9, 0xba, 0x1a, 0x15, 0xd9, 0x5f, 0x95, 0x71,
    0x00, 0x69, 0xe4, 0xa5, 0x8c, 0xee, 0x6a, 0x87, 0x5f, 0x46, 0x73, 0x1b, 0x39, 0x7c,
    0x78, 0xd9, 0xb3, 0x06, 0x7b, 0x57, 0x40, 0xe4, 0x13, 0x9b, 0x94, 0x84, 0x4d, 0x64,
    0xd5, 0x70, 0xfb, 0x0d, 0xf8, 0x34, 0xb5, 0x1c, 0xb8, 0x64, 0x40, 0x26, 0x2e, 0x02,
    0x13, 0x09, 0x51, 0x38, 0xe6, 0x19, 0x43, 0x08, 0x63, 0x33, 0x68, 0x86, 0xb0, 0x7c,
    0x1a, 0x2d, 0x29, 0x03, 0x3e, 0xfd, 0x01, 0x98, 0x3c, 0xa0, 0x8a, 0x81, 0x47, 0xf2,
    0x0c, 0xdc, 0x6b, 0xca, 0xd9, 0xeb, 0x6d, 0x29, 0x34, 0xf6, 0x4b, 0x02, 0x03, 0x01,
    0x00, 0x01, 0xa3, 0x81, 0xcf, 0x30, 0x81, 0xcc, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d,
    0x0e, 0x04, 0x16, 0x04, 0x14, 0x7f, 0x1f, 0x47, 0x68, 0xc6, 0x55, 0x5f, 0x55, 0xf2,
    0x10, 0x3f, 0xc0, 0x05, 0x98, 0xeb, 0x1b, 0x4e, 0xf5, 0x63, 0x80, 0x30, 0x1f, 0x06,
    0x03, 0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x7f, 0x1f, 0x47, 0x68,
    0xc6, 0x55, 0x5f, 0x55, 0xf2, 0x10, 0x3f, 0xc0, 0x05, 0x98, 0xeb, 0x1b, 0x4e, 0xf5,
    0x63, 0x80, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x04, 0x02, 0x30, 0x00, 0x30,
    0x0b, 0x06, 0x03, 0x55, 0x1d, 0x0f, 0x04, 0x04, 0x03, 0x02, 0x02, 0xf4, 0x30, 0x1d,
    0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x16, 0x30, 0x14, 0x06, 0x08, 0x2b, 0x06, 0x01,
    0x05, 0x05, 0x07, 0x03, 0x01, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03,
    0x02, 0x30, 0x53, 0x06, 0x03, 0x55, 0x1d, 0x11, 0x04, 0x4c, 0x30, 0x4a, 0x82, 0x0c,
    0x65, 0x61, 0x63, 0x66, 0x30, 0x35, 0x61, 0x64, 0x32, 0x64, 0x64, 0x65, 0x82, 0x0c,
    0x65, 0x61, 0x63, 0x66, 0x30, 0x35, 0x61, 0x64, 0x32, 0x64, 0x64, 0x65, 0x87, 0x04,
    0xac, 0x11, 0x00, 0x02, 0x87, 0x04, 0x7f, 0x00, 0x00, 0x01, 0x86, 0x20, 0x75, 0x72,
    0x6e, 0x3a, 0x6f, 0x70, 0x65, 0x6e, 0x36, 0x32, 0x35, 0x34, 0x31, 0x2e, 0x73, 0x65,
    0x72, 0x76, 0x65, 0x72, 0x2e, 0x61, 0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x74, 0x69,
    0x6f, 0x6e, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
    0x0b, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0x1f, 0x74, 0x46, 0x12, 0xfd, 0x08,
    0x59, 0x22, 0x47, 0x62, 0x7b, 0xdc, 0xf5, 0xe4, 0xeb, 0x37, 0xb2, 0xb1, 0x63, 0xa8,
    0x60, 0xe7, 0x2c, 0x58, 0x38, 0x32, 0x6d, 0xe5, 0x19, 0x87, 0x10, 0x2a, 0xed, 0x71,
    0x41, 0x05, 0x25, 0xc1, 0x7c, 0xdc, 0x49, 0xbd, 0x45, 0xe6, 0x09, 0xba, 0x2b, 0x05,
    0x22, 0x97, 0x78, 0x34, 0x59, 0x24, 0x92, 0x51, 0xb1, 0x8e, 0xd9, 0x49, 0x25, 0xaf,
    0x1d, 0x93, 0xb1, 0xc9, 0xbd, 0xd9, 0x0a, 0xa8, 0x8e, 0xea, 0x95, 0xb1, 0xdc, 0x30,
    0x17, 0xd3, 0xed, 0x56, 0x88, 0xb3, 0x2e, 0x4f, 0x5f, 0x61, 0x47, 0x34, 0xe0, 0x83,
    0x6d, 0x02, 0xfa, 0xee, 0x8e, 0x09, 0xf7, 0x6a, 0x01, 0xed, 0x89, 0xf9, 0x4f, 0x8e,
    0xea, 0x58, 0xc3, 0xe6, 0x22, 0x4c, 0x54, 0xe6, 0xaa, 0x2f, 0x23, 0xbd, 0x29, 0xba,
    0xdb, 0x15, 0x82, 0x03, 0x0e, 0x8b, 0xb5, 0xc1, 0x35, 0x08, 0x2f, 0x14, 0x58, 0x6b,
    0x5d, 0xa5, 0xa4, 0x4a, 0x8f, 0x8f, 0xe7, 0x38, 0x22, 0x10, 0x7f, 0x46, 0x30, 0x55,
    0x02, 0xee, 0xf3, 0x38, 0x87, 0x78, 0x61, 0x16, 0x77, 0x40, 0x7a, 0xaa, 0x54, 0xf7,
    0xcd, 0xf9, 0x45, 0xd3, 0x17, 0x15, 0x05, 0xf2, 0x28, 0x54, 0xf8, 0xa0, 0x51, 0x8f,
    0x03, 0x6a, 0x86, 0x3b, 0x67, 0x65, 0x26, 0xc8, 0x66, 0x4e, 0x11, 0x50, 0x1a, 0x55,
    0xff, 0xc2, 0x98, 0x4c, 0x1a, 0x55, 0xac, 0x16, 0xb3, 0x18, 0x29, 0x82, 0x77, 0x19,
    0x36, 0x5e, 0x64, 0xa3, 0x1b, 0xa8, 0xe1, 0xb0, 0xc6, 0xa9, 0xc3, 0x1c, 0x8a, 0x63,
    0x80, 0x44, 0xca, 0x8f, 0x4e, 0xd9, 0x29, 0x98, 0xc6, 0x21, 0x07, 0xb1, 0x81, 0xaf,
    0xf5, 0xa6, 0xf7, 0x02, 0xe9, 0xfc, 0x4a, 0x94, 0x2b, 0x91, 0x4e, 0xc3, 0x3a, 0xb1,
    0x01, 0xd4, 0x38, 0xbb, 0x93, 0xa2, 0x20, 0x78, 0xb4, 0xac, 0xbc, 0xec};

static void setup(void) {
    running = true;

    /* Load certificate and private key */
    UA_ByteString certificate;
    certificate.length = CERT_PEM_LENGTH;
    certificate.data = CERT_PEM_DATA;

    UA_ByteString privateKey;
    privateKey.length = KEY_PEM_LENGTH;
    privateKey.data = KEY_PEM_DATA;

    server = UA_Server_new();
    ck_assert(server != NULL);
    UA_ServerConfig *config = UA_Server_getConfig(server);

#ifndef __linux__
    /* Load the trustlist */
    size_t trustListSize = 0;
    UA_ByteString *trustList = NULL;

    /* Load the issuerList */
    size_t issuerListSize = 0;
    UA_ByteString *issuerList = NULL;

    /* Revocation lists are supported, but not used here */
    UA_ByteString *revocationList = NULL;
    size_t revocationListSize = 0;

    UA_StatusCode res =
        UA_ServerConfig_setDefaultWithSecurityPolicies(config, 4840,
                                                       &certificate, &privateKey,
                                                       trustList, trustListSize,
                                                       issuerList, issuerListSize,
                                                       revocationList, revocationListSize);
        ck_assert_uint_eq(res, UA_STATUSCODE_GOOD);
#else /* On Linux we can monitor the certs folder and reload when changes are made */
    UA_StatusCode res =
        UA_ServerConfig_setDefaultWithSecurityPolicies(config, 4840,
                                                       &certificate, &privateKey,
                                                       NULL, 0, NULL, 0, NULL, 0);
    ck_assert_uint_eq(res, UA_STATUSCODE_GOOD);

    res |= UA_CertificateVerification_CertFolders(&config->secureChannelPKI,
                                                  NULL, NULL, NULL, ".");
    res |= UA_CertificateVerification_CertFolders(&config->sessionPKI,
                                                  NULL, NULL, NULL, ".");
    ck_assert_uint_eq(res, UA_STATUSCODE_GOOD);
#endif /* __linux__ */

    /* Set the ApplicationUri used in the certificate */
    UA_String_clear(&config->applicationDescription.applicationUri);
    config->applicationDescription.applicationUri =
        UA_STRING_ALLOC("urn:unconfigured:application");

    UA_Server_run_startup(server);
    THREAD_CREATE(server_thread, serverloop);
}

static void teardown(void) {
    running = false;
    THREAD_JOIN(server_thread);
    UA_Server_run_shutdown(server);
    UA_Server_delete(server);
}

START_TEST(encryption_connect_reject_cert) {
    UA_Client *client = NULL;
    UA_EndpointDescription* endpointArray = NULL;
    size_t endpointArraySize = 0;
    UA_ByteString *trustList = NULL;
    size_t trustListSize = 0;
    UA_ByteString *revocationList = NULL;
    size_t revocationListSize = 0;

    /* Load certificate and private key */
    UA_ByteString certificate;
    const size_t certPemLength = sizeof(clientCertificatePem) / sizeof(clientCertificatePem[0]);
    certificate.length = certPemLength;
    certificate.data = clientCertificatePem;
    ck_assert_uint_ne(certificate.length, 0);

    UA_ByteString privateKey;
    privateKey.length = sizeof(clientCertificateKey) / sizeof(clientCertificateKey[0]);
    privateKey.data = clientCertificateKey;
    ck_assert_uint_ne(privateKey.length, 0);

    /* The Get endpoint (discovery service) is done with
     * security mode as none to see the server's capability
     * and certificate */
    client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    ck_assert(client != NULL);
    UA_StatusCode retval = UA_Client_getEndpoints(client, "opc.tcp://localhost:4840",
                                                  &endpointArraySize, &endpointArray);
    ck_assert_uint_eq(retval, UA_STATUSCODE_GOOD);
    ck_assert(endpointArraySize > 0);

    UA_Array_delete(endpointArray, endpointArraySize,
                    &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

    UA_Client_delete(client);
    
    /* Secure client initialization */
    client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client);
    UA_ClientConfig_setDefaultEncryption(cc, certificate, privateKey,
                                         trustList, trustListSize,
                                         revocationList, revocationListSize);
    cc->securityPolicyUri =
        UA_STRING_ALLOC("http://opcfoundation.org/UA/SecurityPolicy#Aes128_Sha256_RsaOaep");
    ck_assert(client != NULL);

    for(size_t deleteCount = 0; deleteCount < trustListSize; deleteCount++) {
        UA_ByteString_clear(&trustList[deleteCount]);
    }

#ifdef __linux__
    /* Secure client connect */
    retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    ck_assert_uint_eq(retval, UA_STATUSCODE_BADCERTIFICATETIMEINVALID);

    char rejectedFileName [256] = {0};
    strcat(rejectedFileName, "./");
    strcat(rejectedFileName, (char *)clientCertificateThumbprint);
    strcat(rejectedFileName, ".der");
    FILE * fp_rejectedFile = fopen(rejectedFileName, "rb");

    if (fp_rejectedFile) {
        UA_Byte readBuffer[CLIENT_CERTIFICATE_DER_SIZE] = {0};
        fread(readBuffer, CLIENT_CERTIFICATE_DER_SIZE, 1, fp_rejectedFile);

        for(size_t i=0; i<CLIENT_CERTIFICATE_DER_SIZE; i++) {
           ck_assert(readBuffer[i] == clientCertificateDer[i]);
        }
        fclose(fp_rejectedFile);
    }

    UA_Client_disconnect(client);
#endif
    UA_Client_delete(client);
}
END_TEST

static Suite* testSuite_saveRejectedCert(void) {
    Suite *s = suite_create("Encryption");
    TCase *tc_reject_cert = tcase_create("Check saving rejected client certificate");
    tcase_add_checked_fixture(tc_reject_cert, setup, teardown);
    tcase_add_test(tc_reject_cert, encryption_connect_reject_cert);
    suite_add_tcase(s,tc_reject_cert);
    return s;
}

int main(void) {
    Suite *s = testSuite_saveRejectedCert();
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr,CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
