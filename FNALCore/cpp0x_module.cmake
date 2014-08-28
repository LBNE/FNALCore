#-----------------------------------------------------------------------
# Configure cpp0x for C++11 support
# - Convert CheckCXX11Features variables to CPP0X's internal names
set(CPP0X_HAS_AUTO ${HAS_CXX11_AUTO})
set(CPP0X_HAS_CONSTEXPR_FUNCTIONS ${HAS_CXX11_CONSTEXPR})
set(CPP0X_HAS_CONSTEXPR_VARIABLES ${HAS_CXX11_CONSTEXPR})
set(CPP0X_HAS_DECLTYPE ${HAS_CXX11_DECLTYPE})
set(CPP0X_HAS_EXPLICIT_CONVERSION_OPERATORS ${HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS})
set(CPP0X_HAS_FCTN_TEMPLATE_DEFAULT_ARGS ${HAS_CXX11_DEFAULT_TEMPLATE_ARGUMENTS})
set(CPP0X_HAS_LAMBDAS ${HAS_CXX11_LAMBDA})
set(CPP0X_HAS_NOEXCEPT ${HAS_CXX11_NOEXCEPT})
set(CPP0X_HAS_NULLPTR ${HAS_CXX11_NULLPTR})
set(CPP0X_HAS_RVALUE_REFERENCES ${HAS_CXX11_RVALUE_REFERENCES})
set(CPP0X_HAS_STATIC_ASSERT ${HAS_CXX11_STATIC_ASSERT})
set(CPP0X_HAS_VARIADIC_TEMPLATES ${HAS_CXX11_VARIADIC_TEMPLATES})
set(CPP0X_HAS_ALGORITHM_ALL_OF ${HAS_CXX11_ALGORITHM_ALL_OF})
set(CPP0X_HAS_ALGORITHM_ANY_OF ${HAS_CXX11_ALGORITHM_ANY_OF})
set(CPP0X_HAS_ALGORITHM_COPY_N ${HAS_CXX11_ALGORITHM_COPY_N})
set(CPP0X_HAS_ALGORITHM_FIND_IF_NOT ${HAS_CXX11_ALGORITHM_FIND_IF_NOT})
set(CPP0X_HAS_ALGORITHM_IS_PARTITIONED ${HAS_CXX11_ALGORITHM_IS_PARTITIONED})
set(CPP0X_HAS_ALGORITHM_IS_SORTED ${HAS_CXX11_ALGORITHM_IS_SORTED})
set(CPP0X_HAS_ALGORITHM_MIN_MAX ${HAS_CXX11_ALGORITHM_MIN_MAX})
set(CPP0X_HAS_ALGORITHM_NONE_OF ${HAS_CXX11_ALGORITHM_NONE_OF})
set(CPP0X_HAS_ALGORITHM_PARTITION_POINT ${HAS_CXX11_ALGORITHM_PARTITION_POINT})
set(CPP0X_HAS_ALGORITHM_SHUFFLE ${HAS_CXX11_ALGORITHM_SHUFFLE})
set(CPP0X_HAS_ARRAY_HDR ${HAS_CXX11_ARRAY})
set(CPP0X_HAS_CMATH_C99 ${HAS_CXX11_CMATH_C99})
set(CPP0X_HAS_CMATH_FPCLASSIFICATION ${HAS_CXX11_CMATH_FPCLASSIFY})
set(CPP0X_HAS_CSTDDEF_NULLPTR_T ${HAS_CXX11_CSTDDEF_NULLPTR_T})
set(CPP0X_HAS_CSTDINT_HDR ${HAS_CXX11_CSTDINT_H})
set(CPP0X_HAS_FUNCTIONAL_BIND ${HAS_CXX11_FUNCTIONAL_BIND})
set(CPP0X_HAS_FUNCTIONAL_FUNCTION ${HAS_CXX11_FUNCTIONAL_FUNCTION})
set(CPP0X_HAS_FUNCTIONAL_HASH ${HAS_CXX11_FUNCTIONAL_HASH})
set(CPP0X_HAS_FUNCTIONAL_MEM_FN ${HAS_CXX11_FUNCTIONAL_MEM_FN})
set(CPP0X_HAS_FUNCTIONAL_REFERENCE_WRAPPER ${HAS_CXX11_FUNCTIONAL_REF})
set(CPP0X_HAS_ITERATOR_RANGE ${HAS_CXX11_RANGE_BASED_FOR})
set(CPP0X_HAS_MEMORY_SHARED_PTR ${HAS_CXX11_MEMORY_SHARED_PTR})
set(CPP0X_HAS_MEMORY_UNIQUE_PTR ${HAS_CXX11_MEMORY_UNIQUE_PTR})
set(CPP0X_HAS_NUMERIC_IOTA ${HAS_CXX11_NUMERIC_IOTA})
set(CPP0X_HAS_RANDOM_HDR ${HAS_CXX11_RANDOM})
set(CPP0X_HAS_REGEX_HDR ${HAS_CXX11_LIB_REGEX})
set(CPP0X_HAS_STRING_NUMERIC_CONVERSIONS ${HAS_CXX11_STRING_NUMERIC_CONVERSIONS}
)
set(CPP0X_HAS_SYSTEM_ERROR_HDR ${HAS_CXX11_SYSTEM_ERROR})
set(CPP0X_HAS_TUPLE_HDR ${HAS_CXX11_TUPLE})
set(CPP0X_HAS_TYPE_TRAITS_HDR ${HAS_CXX11_TYPE_TRAITS})
set(CPP0X_HAS_UTILITY_DECLVAL ${HAS_CXX11_UTILITY_DECLVAL})


# - Build cpp0x
set( PUBLIC_HDRS
  algorithm
  array
  cmath
  cstddef
  cstdint
  functional
  iterator
  memory
  numeric
  random
  regex
  string
  system_error
  tuple
  type_traits
  utility
)

set( DETAIL_HDRS
  detail/a_x_plus_c_mod_m
  detail/add_rv_ref
  detail/bernoulli_distribution
  detail/binomial_distribution
  detail/cauchy_distribution
  detail/chi_squared_distribution
  detail/declval
  detail/discard_block_engine
  detail/discrete_distribution
  detail/exponential_distribution
  detail/extreme_value_distribution
  detail/fisher_f_distribution
  detail/gamma_distribution
  detail/generate_canonical
  detail/geometric_distribution
  detail/independent_bits_engine
  detail/is_nonnegative
  detail/is_sseq
  detail/linear_congruential_engine
  detail/log2
  detail/lognormal_distribution
  detail/low_order_bits
  detail/mersenne_twister_engine
  detail/negative_binomial_distribution
  detail/normal_distribution
  detail/nullptr
  detail/piecewise_constant_distribution
  detail/piecewise_linear_distribution
  detail/poisson_distribution
  detail/pow2
  detail/predefined_engine_types
  detail/random_device
  detail/seed_seq
  detail/shuffle_order_engine
  detail/stats
  detail/stream_state_guard
  detail/student_t_distribution
  detail/subtract_with_carry_engine
  detail/uniform_int_distribution
  detail/uniform_real_distribution
  detail/unique_ptr
  detail/weibull_distribution
)

configure_file(detail/config.in ${CMAKE_CURRENT_BINARY_DIR}/detail/config)
list(APPEND DETAIL_HDRS ${CMAKE_CURRENT_BINARY_DIR}/detail/config)

set_source_files_properties(${PUBLIC_HDRS} ${DETAIL_HDRS}
  PROPERTIES
    HEADER_FILE_ONLY TRUE
  )

#-----------------------------------------------------------------------
# Create a dummy library to check export
add_library(cpp0x OBJECT dummy.cc ${PUBLIC_HDRS} ${DETAIL_HDRS})

# TEMP local install of headers
install(FILES ${PUBLIC_HDRS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/cpp0x
  COMPONENT Development
  )
install(FILES ${DETAIL_HDRS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/cpp0x/detail
  COMPONENT Development
  )

#-----------------------------------------------------------------------
# Test if required
if(FNALCore_ENABLE_TESTING)
  add_subdirectory(unittests)
endif()


