/*
 * Google Cloud Certificates
 * Copyright (c) 2019-2020, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AZURE_CLOUD_CREDENTIALS_H
#define AZURE_CLOUD_CREDENTIALS_H

namespace azure_cloud {
namespace credentials {
/*
 * Primary Connecion String
 */

// Use https://dpsgen.z8.web.core.windows.net/ to obtain YOUR connection string
// This one will not work, but I guess you knew that ;)
const char iothub_connection_string[] = "HostName=iotc-c2dd98d8-fcdb-485c-9f10-9f15250ad05a.azure-devices.net;DeviceId=1ihhjwmthyh;SharedAccessKey=V+r5zstilUDIZVSp9qmO89Mn1l8u9sK4EhRQUZhpHoA=";
} // namespace credentials
} // namespace azure_cloud
#endif
