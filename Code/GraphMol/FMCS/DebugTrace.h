// $Id$
//
//  Copyright (C) 2014 Novartis Institutes for BioMedical Research
//
//   @@ All Rights Reserved @@
//  This file is part of the RDKit.
//  The contents are covered by the terms of the BSD license
//  which is included in the file license.txt, found at the root
//  of the RDKit source tree.
//
#pragma once
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <iostream>
#ifdef WIN32
    #include <Windows.h> // for Winmm.lib timeGetTime()
    #ifdef _DEBUG   // check memory leaks
        #include <crtdbg.h>
        #define _CRTDBG_MAP_ALLOC
        #ifndef new
            #define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
        #endif
    #endif
#else
    #include <unistd.h>
    #include <fcntl.h>
#endif

// SELECT ALGORITHM OPTIONS by comment some lines to exclude additional or experimental optimisations:

#define SEED_GROW_DEEP              // fast and works much times faster (but it can depend on molecules)
//#define EXCLUDE_WRONG_COMPOSITION   // fast but with a little effect, because amount of external bonds usually is very small.
                                    // Exclude mismatched bonds combinations during seed growing (2^N-1 stage)

#define FAST_SUBSTRUCT_CACHE        // based on Morgan code hash
#define DUP_SUBSTRUCT_CACHE         // based on list of query atoms and bonds. For rings where seeds growing in both directions throw the same ring.

#define PRECOMPUTED_TABLES_MATCH    // Improves overal performance about 20%, especially in hard cases.
                                    // Takes some extra memory (Vt*vq+Et*eq)/8 bytes for each target G(Vt,Et) matched with query G(vq,eq).

#define FAST_INCREMENTAL_MATCH      // fast and some time very usefull
                                    // previous match result based match checking without finding new matched substructure location in the target

#ifdef RDK_THREADSAFE_SSS
    #define MULTI_THREAD // experimental !
#endif

// Enable / Disable DEBUG TRACE output
#ifdef WIN32__xx__TRACE_ON
    #define TRACE_ON
#else
#endif

#ifndef MULTI_THREAD
    #define VERBOSE_STATISTICS_ON
#endif


#ifdef VERBOSE_STATISTICS_ON

// compute statistics of really very very fast calls. 
// It a bit decrease overal performance, but might be interested for investigation purpose (only)
//#define VERBOSE_STATISTICS_FASTCALLS_ON

    struct ExecStatistics
    {
        unsigned TotalSteps, MCSFoundStep;
        time_t   MCSFoundTime;  // approximately
        unsigned InitialSeed, MismatchedInitialSeed;
        unsigned Seed, RemainingSizeRejected;
        unsigned SeedCheck, SingleBondExcluded;
        unsigned MatchCall, MatchCallTrue;
        unsigned FastMatchCall, FastMatchCallTrue, SlowMatchCallTrue;
        unsigned ExactMatchCall, ExactMatchCallTrue;   // hash cache
        unsigned FindHashInCache, HashKeyFoundInCache;
#ifdef SMILES_CACHE
        unsigned FindInMatchedCache, FoundInMatchedCache;
        unsigned FindInDoNotMatchedCache, FoundInDoNotMatchedCache;
#endif
        unsigned AtomCompareCalls, BondCompareCalls;    // long long
        unsigned AtomFunctorCalls, BondFunctorCalls;    // long long
        unsigned WrongCompositionRejected, WrongCompositionDetected;
        unsigned DupCacheFound, DupCacheFoundMatch;

        ExecStatistics() : TotalSteps(0), MCSFoundStep(0)
                         , MCSFoundTime(time(0))
                         , InitialSeed(0), MismatchedInitialSeed(0)
                         , Seed(0), RemainingSizeRejected(0)
                         , SeedCheck(0), SingleBondExcluded(0), MatchCall(0), MatchCallTrue(0)
                         , FastMatchCall(0), FastMatchCallTrue(0), SlowMatchCallTrue(0)
                         , ExactMatchCall(0), ExactMatchCallTrue(0)
                         , FindHashInCache(0), HashKeyFoundInCache(0)
#ifdef SMILES_CACHE
                         , FindInMatchedCache(0), FoundInMatchedCache(0)
                         , FindInDoNotMatchedCache(0), FoundInDoNotMatchedCache(0)
#endif
                         , AtomCompareCalls(0), BondCompareCalls(0)
                         , AtomFunctorCalls(0), BondFunctorCalls(0)
                         , WrongCompositionRejected(0), WrongCompositionDetected(0)
                         , DupCacheFound(0), DupCacheFoundMatch(0)
        {}
    };
#endif

namespace RDKit
{
 namespace FMCS
 {
#ifdef TRACE_ON
     std::ostream& TRACE(unsigned info=1)
     {
         if(info > 0)   // print out time
         {
            struct tm *now;
            char strt[32], strts[12];
            #ifdef WIN32
                static unsigned long t0 = timeGetTime();                        see gettimeofday for Win in test.cpp
                typedef struct timespec
                {
	                time_t tv_sec;  // Seconds since 00:00:00 GMT = 1 January 1970
	                long   tv_nsec; // Additional nanoseconds since Windows started - assume since tv_sec
                } timespec;

                struct timespec ts;
	            //time( &(ts.tv_sec) );
                unsigned long t = timeGetTime() - t0; // t from app started
                ts.tv_sec  =  t / 1000LU;
	            ts.tv_nsec = (t % 1000LU)*1000000LU;     // nanoseconds.
            #else
                struct timespec ts;
                //clock_gettime(CLOCK_REALTIME, &ts);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
            #endif

            now = gmtime(&ts.tv_sec);
            if(now != NULL)
                strftime(strt, sizeof(strt), "%H:%M:%S", now); //strftime(strt, sizeof(strt), "%Y-%m-%d %H:%M:%S", now);

            #ifdef WIN32
                sprintf(strts, ".%03lu ", ts.tv_nsec / 1000000LU);
            #else
                sprintf(strts, ".%05lu ", ts.tv_nsec / 10000LU);
            #endif

            std::cout << strt << strts;
        }
        return std::cout;
     }
#else
     class NullStream
     {
     public:
        template<class T>
        NullStream& operator << (const T&) {return *this;}  // DO NOTHING
     };
     static inline NullStream& TRACE(unsigned info=1) { static NullStream z; return z; }
#endif
}}
