/***************************************************************************************************

Copyright (c) 2019 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#pragma once

#include "BoostLibWrapper.h"

#include "Sugar.h"
#include "Configure.h"
#include "SimulationEnums.h"
#include "ISusceptibilityContext.h"

class Configuration;

namespace Kernel
{
    struct IIndividualHumanContext;
    class SimulationConfig;

    class SusceptibilityConfig : public JsonConfigurable 
    {
        friend class Individual;

    public:
        virtual bool Configure( const Configuration* config ) override;

        static bool                     enable_initial_susceptibility_distribution;
        static DistributionType::Enum   susceptibility_initialization_distribution_type;

    protected:
        friend class Susceptibility;
        static SusceptibilityType::Enum        susceptibility_type;

        static bool  maternal_protection;
        static MaternalProtectionType::Enum    maternal_protection_type;
        static float matlin_slope;
        static float matlin_suszero;
        static float matsig_steepfac;
        static float matsig_halfmax;
        static float matsig_susinit;

        static float baseacqupdate;
        static float basetranupdate;
        static float basemortupdate;
        
        static bool  enable_immune_decay;
        static float acqdecayrate;
        static float trandecayrate;
        static float mortdecayrate;
        static float baseacqoffset;
        static float basetranoffset;
        static float basemortoffset;

        void LogConfigs() const;

        GET_SCHEMA_STATIC_WRAPPER(SusceptibilityConfig)
        IMPLEMENT_DEFAULT_REFERENCE_COUNTING()
        DECLARE_QUERY_INTERFACE()
    };

    class Susceptibility : public ISusceptibilityContext
    {
        IMPLEMENT_DEFAULT_REFERENCE_COUNTING()
        DECLARE_QUERY_INTERFACE()
    public:
        static Susceptibility *Susceptibility::CreateSusceptibility(IIndividualHumanContext *context, float _age, float immmod, float riskmod);
        virtual ~Susceptibility();
        virtual void SetContextTo(IIndividualHumanContext* context);
        IIndividualHumanContext* GetParent();

        virtual void  Update(float dt=0.0);
        virtual void  UpdateInfectionCleared();

        // ISusceptibilityContext interfaces
        virtual float getAge() const override;
        virtual float getModAcquire() const override;
        virtual float getModTransmit() const override;
        virtual float getModMortality() const override;
        virtual float getImmuneFailage() const override;
        virtual void  updateModAcquire(float updateVal) override;
        virtual void  updateModTransmit(float updateVal) override;
        virtual void  updateModMortality(float updateVal) override;
        virtual void  setImmuneFailage(float newFailage) override;
        virtual void  InitNewInfection() override;
        virtual bool  IsImmune() const override;

    protected:
        // current status
        float age;

        // immune modifiers
        float mod_acquire;
        float mod_transmit;
        float mod_mortality;

        float acqdecayoffset;
        float trandecayoffset;
        float mortdecayoffset;

        float immune_failage;

        Susceptibility();
        Susceptibility(IIndividualHumanContext *context);
        virtual void Initialize(float _age, float immmod, float riskmod);

        IIndividualHumanContext *parent;

        const SimulationConfig* params();

        DECLARE_SERIALIZABLE(Susceptibility);
    };
}
