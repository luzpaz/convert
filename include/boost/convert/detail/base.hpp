// Copyright (c) 2009-2014 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_CONVERTER_BASE_HPP
#define BOOST_CONVERT_CONVERTER_BASE_HPP

#include <boost/convert/parameters.hpp>

namespace boost { namespace cnv { namespace detail
{
    template<typename> struct cnvbase;
}}}

template<typename derived>
struct boost::cnv::detail::cnvbase
{
    typedef cnvbase this_type;

    cnvbase()
    :
        base_(10), precision_(0), uppercase_(false)
    {}

    derived const&
    operator()(boost::parameter::aux::tag<boost::cnv::parameter::type::base, boost::cnv::base::type const>::type const& arg) const
    {
        boost::cnv::base::type base = arg[cnv::parameter::base];
        
        base_ = base == cnv::base::dec ? 10
              : base == cnv::base::hex ? 16
              : base == cnv::base::oct ? 8 : 0;

        return dncast();
    }
    derived const&
    operator()(boost::parameter::aux::tag<boost::cnv::parameter::type::precision, int const>::type const& arg) const
    {
        precision_ = arg[cnv::parameter::precision];

        return dncast();
    }
    derived const&
    operator()(boost::parameter::aux::tag<boost::cnv::parameter::type::uppercase, bool const>::type const& arg) const
    {
        uppercase_ = arg[cnv::parameter::uppercase];

        return dncast();
    }
    
    protected:

    derived const& dncast() const { return *static_cast<derived const*>(this); }

    int mutable       base_;
    int mutable  precision_;
    bool mutable uppercase_;
};

#define CONVERTER_PARAM_FUNC(PARAM_NAME, PARAM_TYPE)    \
    this_type&                                          \
    operator()(boost::parameter::aux::tag<boost::cnv::parameter::type::PARAM_NAME, PARAM_TYPE const>::type const& arg)

#endif // BOOST_CONVERT_CONVERTER_BASE_HPP
