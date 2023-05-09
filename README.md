# Plant Sensor Program
## Overview
This project is for the purpose of computerising the detection of environmental information
related to plant health and making adjustments to their environment where possible. Notably,
it will be for the purpose of measuring water levels in plant soil in order to adjust these water
levels either through automated or manual watering in order to meet the optimum
requirements of the plants. This should increase the efficiency and ease of undertaking
these tasks. Automated watering will not take place in this instance of the project.

## This Repository
In order to acquire sensor data, this back-end application is required in order to process said
data and send it to the MQTT Mosquitto server. This back-end application is currently set up
to automatically and perpetually monitor the light, moisture, temperature and humidity levels
of a plant. As one instance of this application runs on one Nucleo embedded board, only one
plant is monitored per application.

## Technology
The Plant Sensing and Monitoring System will utilise an embedded single board computer
that has the ability to detect water levels for the purpose of detecting them in plant soil. This
will be achieved with C++ code. Data concerning the plant health will be sent to a cloud
server, which will be retrieved by a desktop application in order for presentable and
abstracted user viewing. The desktop application will be written in C++ with the use of the
QT framework. For this reason, it will be able to be distributed to build natively for both
mobile and desktop environments. Mosquitto will be used in order to facilitate
device-to-cloud and cloud-to-device connection through the use of the MQTT Protocol.
## Stakeholders
The Plant Sensing and Monitoring System will be, paramount, for the sake of aiding the
developer of this project. The reason for this is due to the fact that the developer participates
in amateur horticulture. Additionally, the Plant Sensing and Monitoring System would also be
equally beneficial for any other amateur horticulturalists. If extended upon in scope, it could
then become beneficial for professional, industrial horticulture.
## Purpose
The purpose of the Plant Sensing and Monitoring System is derived from the principal issue
that watering plants and checking their health in general traditionally requires consistent
manual labour. This of course requires time, which is an issue for amateur horticulturalists
who, in particular, may often not have an extensive amount of time to attend to their plants.
Correspondingly, it is also a larger scale issue within an industrial context, where consistent
and time consuming manual labour requires significant expenditures. For this reason, the
Plant Sensing and Monitoring System could conserve significant amounts of time and money
for amateurs, and with further development, for professionals also.
