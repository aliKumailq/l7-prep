#ifndef PACK_H
#define PACK_H


namespace pack_detail {
    template <typename... Args>
    constexpr int packSize = 1;

    template <typename Arg, typename... Args>
    constexpr int packSize<Arg, Args...> = 1 + packSize<Args...>;




    template <int QueryIndex,typename Arg,typename... Args> 
    struct packIndexToType{
        static_assert(QueryIndex >= 0 && QueryIndex < 1 + packSize<Args...>); 
        using type = packIndexToType<QueryIndex -1, Args...>::type;
    };    



    template <typename Arg>
    struct packIndexToType<0, Arg> {
        using type = Arg;

    };

    template <int QueryIndex,typename... Args> 
    using _packIndexToType = packIndexToType<QueryIndex, Args...>::type;



    template <int Accumulated, typename QueryType, typename... Args>
    constexpr int _packTypeToIndex = -(Accumulated + 1); // if not found

    template<int Accumulated, typename QueryType>
    constexpr int _packTypeToIndex<Accumulated, QueryType, QueryType> = 0; // case when found




}



template <typename... Args>

struct Pack {
    constexpr static int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::_packIndexToType<QueryIndex,Args...>;

};

#endif  // PACK_H
