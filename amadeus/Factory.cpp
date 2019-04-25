#include "Factory.h"
#include "AmadeusExports.h"

core::BaseGDS *CreateGDS(map<string, string> _param) {
  return new core::AmadeusGDS(_param);
}