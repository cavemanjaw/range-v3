/// \file
// Range v3 library
//
//  Copyright Andrey Diduh 2019
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_ADDRESSOF_HPP
#define RANGES_V3_VIEW_ADDRESSOF_HPP

#include <type_traits>
#include <utility>

#include <meta/meta.hpp>

#include <range/v3/utility/addressof.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/view.hpp>

namespace ranges
{
    /// \addtogroup group-views
    /// @{
    namespace view
    {
        struct addressof_fn
        {
        private:
            struct take_address
            {
                template<typename V>
                constexpr V * operator()(V & value) const noexcept
                {
                    return detail::addressof(value);
                }
            };

        public:
            CPP_template(typename Rng)(                                      //
                requires ViewableRange<Rng> && InputRange<Rng> &&            //
                    std::is_lvalue_reference<range_reference_t<Rng>>::value) //
                constexpr auto CPP_auto_fun(operator())(Rng && rng)(const)(
                    return transform(all(static_cast<Rng &&>(rng)), take_address{}))
        };

        /// \relates addressof_fn
        /// \ingroup group-views
        RANGES_INLINE_VARIABLE(view<addressof_fn>, addressof)
    }
    /// @}
}

#endif // RANGES_V3_VIEW_ADDRESSOF_HPP
