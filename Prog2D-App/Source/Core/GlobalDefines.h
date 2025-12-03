#pragma once

#define DERIVED_CLASS(myclass, base) \
typedef base Super;

#define UNUSED_VARIABLE(var) (void)var;