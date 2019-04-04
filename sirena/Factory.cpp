#include "Factory.h"
#include "SirenaExports.h"

core::BaseGDS *CreateGDS() { return new core::SirenaGDS(); }