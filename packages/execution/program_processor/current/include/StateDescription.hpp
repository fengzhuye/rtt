/***************************************************************************
  tag: Peter Soetens  Thu Apr 22 20:40:59 CEST 2004  StateDescription.hpp

                        StateDescription.hpp -  description
                           -------------------
    begin                : Thu April 22 2004
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

#ifndef STATE_DESCRIPTION_HPP
#define STATE_DESCRIPTION_HPP

#include "corelib/StateInterface.hpp"
#include "execution/FunctionGraph.hpp"

namespace ORO_Execution
{
    using boost::tie;
    using boost::graph_traits;
    using boost::property_map;
    using std::find_if;
    using std::bind2nd;
    using boost::get;
    using boost::put;

    using ORO_CoreLib::StateInterface;

    /**
     * @brief This class represents a state with all actions stored
     * in an external StateGraph.
     *
     * It keeps track of the entry node,
     * handler node and exit node of a state in a
     * StateGraph.
     */
    class StateDescription
        : public StateInterface
    {
        FunctionGraph* mentry;
        FunctionGraph* mexit;
        FunctionGraph* mhandle;
        bool inited;
        std::string name;
    public:
        /**
         * Construct a new State with entry, exit and handle nodes.
         * The StateGraph owning the nodes is needed for processing each state.
         */
        StateDescription(const std::string& _name )
            : mentry(0), mexit(0), mhandle(0),
               inited(false), name(_name)
        {
        }

        virtual ~StateDescription();

//         StateDescription( const StateDescription& orig )
//             : mentry( orig.entryNode() ),
//               mexit( orig.exitNode() ),
//               mhandle( orig.handleNode() ),
//               inited( orig.isDefined() )
//         {
//         }

        const std::string& getName() const { return name; }

        virtual void onEntry();

        virtual void handle();

        virtual void onExit();

        /**
         * This function returns a new state that contains all the
         * data of this state ( its handle, entry, exit programs, and
         * its name and inited state ), while this state's data is
         * reset ( i.e. its handle, entry, exit programs are set to
         * null, its name is cleared, and it is set to not inited ).
         * This is used by the parser when it suddenly notices that it
         * needs to insert a dummy state before the current to check
         * preconditions.
         */
        StateDescription* postponeState();

        FunctionGraph* getEntryProgram() {
            return mentry;
        }

        FunctionGraph* getHandleProgram() {
            return mhandle;
        }

        FunctionGraph* getExitProgram() {
            return mexit;
        }

        void setEntryProgram( FunctionGraph* entry ) {
            delete mentry;
            mentry = entry;
        }

        void setHandleProgram( FunctionGraph* handle ) {
            delete mhandle;
            mhandle = handle;
        }

        void setExitProgram( FunctionGraph* exit ) {
            delete mexit;
            mexit = exit;
        }

        bool isDefined() const
        {
            return inited;
        }

        void setDefined( bool d ) {
            inited = d;
        }

        StateDescription* copy( std::map<const DataSourceBase*, DataSourceBase*>& replacementdss ) const;

    };
};

#endif
