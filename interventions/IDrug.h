/***************************************************************************************************

Copyright (c) 2019 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#pragma once

#include "ISupports.h"

namespace Kernel
{
    struct IDrug : ISupports
    {
        virtual const std::string& GetDrugName() const = 0;
        virtual float GetDrugCurrentEfficacy() const = 0;
    };
}
