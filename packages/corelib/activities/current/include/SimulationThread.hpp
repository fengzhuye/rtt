/***************************************************************************
  tag: Peter Soetens  Tue Dec 21 22:43:07 CET 2004  SimulationThread.hpp 

                        SimulationThread.hpp -  description
                           -------------------
    begin                : Tue December 21 2004
    copyright            : (C) 2004 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/
 
 

#ifndef SIMULATIONTHREAD_HPP
#define SIMULATIONTHREAD_HPP

#include "TimerThread.hpp"


namespace ORO_CoreLib
{

    class TaskSimulation;
    class TimeService;
    /**
     * This thread is the simulated realtime thread in the
     * Orocos system. It behaves (to the TaskSimulation) like a perfect scheduler.
     * 
     * It Uses the Singleton pattern, since there will be only one.
     *
     * @see PeriodicThread, ZeroTimeThread
     */
    class SimulationThread
        : public TimerThread
    {
    public:
        static SimulationThread* Instance();

        /**
         * Releases the SimulationThread
         * Reference counting might aid in making this call safe
         *
         * @return true on success, false on failure
         */
        static bool Release();

        /**
         * Destructor
         */
        virtual ~SimulationThread();

        using TimerThread::start;

        /**
         * Only run the simulation \a maxsteps time steps, then stop the SimulationThread.
         */
        virtual bool start(unsigned int maxsteps)
        {
            maxsteps_ = maxsteps;
            return TimerThread::start();
        }
                           
    protected:
        bool initialize();
        void step();
        void finalize();

        /**
         * Constructor
         */
        SimulationThread();

    private:

        /**
         * Our only instance of the SimulationThread
         */
        static SimulationThread* _instance;

        /**
         * The System clock.
         */
        TimeService* beat;

        unsigned int maxsteps_, cursteps;
    };
} // namespace ORO_CoreLib

#endif
