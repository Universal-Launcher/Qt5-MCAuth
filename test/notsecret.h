#pragma once

#include <QString>

namespace {
/**
 * To run the test, you need to copy this file to `secret.h` and then add your
 * Azure client ID.
 */

QString clientID = "your_client_id";
} // namespace

namespace Secrets {
QString getMSAClientID() { return clientID; }
}; // namespace Secrets
