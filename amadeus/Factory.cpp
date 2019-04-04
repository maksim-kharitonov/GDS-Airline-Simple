#include "Factory.h"
#include "AmadeusExports.h"

core::BaseGDS *CreateGDS() { return new core::AmadeusGDS(); }