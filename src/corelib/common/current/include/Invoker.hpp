#ifndef ORO_INVOKER_BASE_HPP
#define ORO_INVOKER_BASE_HPP

#include <boost/function_types/function_type.hpp>
#include <boost/function_types/function_type_arity.hpp>
#include "NA.hpp"

namespace RTT
{
    namespace detail
    {
        /**
         * A class which converts a function type signature \a F
         * to a virtual operator()() interface.
         */
        template<int, class F, class R>
        struct InvokerBaseImpl;

        template<class F, class R>
        struct InvokerBaseImpl<0,F,R>
        {
            virtual ~InvokerBaseImpl() {}
            virtual R operator()() = 0;
        };

        template<class F, class R>
        struct InvokerBaseImpl<1,F,R>
        {
            typedef typename boost::function<F>::arg1_type arg1_type;
            virtual ~InvokerBaseImpl() {}
            virtual R operator()(arg1_type a1) = 0;
        };

        template<class F, class R>
        struct InvokerBaseImpl<2,F,R>
        {
            typedef typename boost::function<F>::arg1_type arg1_type;
            typedef typename boost::function<F>::arg2_type arg2_type;
            virtual ~InvokerBaseImpl() {}
            virtual R operator()(arg1_type a1, arg2_type a2) = 0;
        };

        template<class F, class R>
        struct InvokerBaseImpl<3,F,R>
        {
            typedef typename boost::function<F>::arg1_type arg1_type;
            typedef typename boost::function<F>::arg2_type arg2_type;
            typedef typename boost::function<F>::arg3_type arg3_type;
            virtual ~InvokerBaseImpl() {}
            virtual R operator()(arg1_type a1, arg2_type a2, arg3_type a3) = 0;
        };

        template<class F, class R>
        struct InvokerBaseImpl<4,F,R>
        {
            typedef typename boost::function<F>::arg1_type arg1_type;
            typedef typename boost::function<F>::arg2_type arg2_type;
            typedef typename boost::function<F>::arg3_type arg3_type;
            typedef typename boost::function<F>::arg4_type arg4_type;
            virtual ~InvokerBaseImpl() {}
            virtual R operator()(arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4) = 0;
        };

        template<class F>
        struct InvokerBase
            : public InvokerBaseImpl<boost::function_traits<F>::arity, F, typename boost::function_traits<F>::result_type>
        {};

        template<int, class F, class BaseImpl>
        struct InvokerImpl;
        
        template<class F, class BaseImpl>
        struct InvokerImpl<0,F,BaseImpl>
            : public BaseImpl
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            /**
             * Invoke this operator if the method has no arguments.
             */
            result_type operator()()
            {
                return BaseImpl::invoke();
            }
        };

        template<class F, class BaseImpl>
        struct InvokerImpl<1,F,BaseImpl>
            : public BaseImpl
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            /**
             * Invoke this operator if the method has one argument.
             */
            result_type operator()(arg1_type a1)
            {
                return BaseImpl::template invoke<arg1_type>( a1 );
            }
        };

        template<class F, class BaseImpl>
        struct InvokerImpl<2,F,BaseImpl>
            : public BaseImpl
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            typedef typename boost::function_traits<F>::arg2_type arg2_type;

            /**
             * Invoke this operator if the method has two arguments.
             */
            result_type operator()(arg1_type t1, arg2_type t2)
            {
                return BaseImpl::template invoke<arg1_type, arg2_type>(t1, t2);
            }

        };

        template<class F, class BaseImpl>
        struct InvokerImpl<3,F,BaseImpl>
            : public BaseImpl
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            typedef typename boost::function_traits<F>::arg2_type arg2_type;
            typedef typename boost::function_traits<F>::arg3_type arg3_type;

            /**
             * Invoke this operator if the method has three arguments.
             */
            result_type operator()(arg1_type t1, arg2_type t2, arg3_type t3)
            {
                return BaseImpl::template invoke<arg1_type, arg2_type, arg3_type>(t1, t2, t3);
            }

        };

        template<class F, class BaseImpl>
        struct InvokerImpl<4,F,BaseImpl>
            : public BaseImpl
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            typedef typename boost::function_traits<F>::arg2_type arg2_type;
            typedef typename boost::function_traits<F>::arg3_type arg3_type;
            typedef typename boost::function_traits<F>::arg4_type arg4_type;

            /**
             * Invoke this operator if the method has four arguments.
             */
            result_type operator()(arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4)
            {
                return BaseImpl::template invoke<arg1_type, arg2_type, arg3_type, arg4_type>(t1, t2, t3, t4);
            }
            
        };

        /**
         * Creates an invocation object with a function
         * signature to invoke and an implementation in which
         * an operator(args) is available which has this signature.
         */
        template<class F, class BaseImpl>
        struct Invoker
            : public InvokerImpl<boost::function_traits<F>::arity, F, BaseImpl>
        {};


        /**
         * Used by various classes to define operator(), given a Signature.
         * @param int The number of arguments of operator().
         * @param Signature The C-style function signature (function type).
         * @param ToInvoke A class type which is called within operator().
         */
        template<int, class Signature, class ToInvoke>
        struct InvokerSignature;
        
        template<class F, class ToInvoke>
        struct InvokerSignature<0,F,ToInvoke>
        {
            typedef typename boost::function_traits<F>::result_type result_type;

            InvokerSignature() : impl() {}
            InvokerSignature(ToInvoke implementation) : impl(implementation) {}
            ~InvokerSignature() {}

            /**
             * Invoke this operator if the method has no arguments.
             */
            result_type operator()()
            {
                if (impl)
                    return (*impl)();
                return NA<result_type>::na();
            }
        protected:
            ToInvoke impl;
        };

        template<class F, class ToInvoke>
        struct InvokerSignature<1,F,ToInvoke>
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;

            InvokerSignature() : impl() {}
            InvokerSignature(ToInvoke implementation) : impl(implementation) {}
            ~InvokerSignature() {}

            /**
             * Invoke this operator if the method has one argument.
             */
            result_type operator()(arg1_type a1)
            {
                if (impl)
                    return (*impl)( a1 );
                return NA<result_type>::na();
            }
        protected:
            ToInvoke impl;
        };

        template<class F, class ToInvoke>
        struct InvokerSignature<2,F,ToInvoke>
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            typedef typename boost::function_traits<F>::arg2_type arg2_type;

            InvokerSignature() : impl() {}
            InvokerSignature(ToInvoke implementation) : impl(implementation) {}
            ~InvokerSignature() {}

            /**
             * Invoke this operator if the method has two arguments.
             */
            result_type operator()(arg1_type t1, arg2_type t2)
            {
                if (impl)
                    return (*impl)(t1, t2);
                return NA<result_type>::na();
            }

        protected:
            ToInvoke impl;
        };

        template<class F, class ToInvoke>
        struct InvokerSignature<3,F,ToInvoke>
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            typedef typename boost::function_traits<F>::arg2_type arg2_type;
            typedef typename boost::function_traits<F>::arg3_type arg3_type;

            InvokerSignature() : impl() {}
            InvokerSignature(ToInvoke implementation) : impl(implementation) {}
            ~InvokerSignature() { }

            /**
             * Invoke this operator if the method has three arguments.
             */
            result_type operator()(arg1_type t1, arg2_type t2, arg3_type t3)
            {
                if (impl)
                    return (*impl)(t1, t2, t3);
                return NA<result_type>::na();
            }

        protected:
            ToInvoke impl;
        };

        template<class F, class ToInvoke>
        struct InvokerSignature<4,F,ToInvoke>
        {
            typedef typename boost::function_traits<F>::result_type result_type;
            typedef typename boost::function_traits<F>::arg1_type arg1_type;
            typedef typename boost::function_traits<F>::arg2_type arg2_type;
            typedef typename boost::function_traits<F>::arg3_type arg3_type;
            typedef typename boost::function_traits<F>::arg4_type arg4_type;

            InvokerSignature() : impl() {}
            InvokerSignature(ToInvoke implementation) : impl(implementation) {}
            ~InvokerSignature() { }

            /**
             * Invoke this operator if the method has four arguments.
             */
            result_type operator()(arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4)
            {
                if (impl)
                    return (*impl)(t1, t2, t3, t4);
                return NA<result_type>::na();
            }
            
        protected:
            ToInvoke impl;
        };

    }
}
#endif