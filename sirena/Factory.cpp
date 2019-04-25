#include "Factory.h"
#include "SirenaExports.h"

core::BaseGDS *CreateGDS(map<string, string> _param) {
  return new core::SirenaGDS(_param);
}