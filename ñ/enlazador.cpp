/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include "lld/Common/Driver.h"

#include "enlazador.hpp"

namespace Ñ
{
    int enlaza(std::vector<const char *> argumentos)
    {
        return lld::coff::link(argumentos, true, llvm::outs(), llvm::errs());
    }

} // namespace Ñ
