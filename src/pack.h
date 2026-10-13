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


    //    template <int Accumulated, typename QueryType, typename... Args>

    template <int Acc, typename QueryType, typename... Args>
    constexpr int _p = -1; // not found


    template <int Acc, typename QueryType,typename Arg ,typename... Args>
    constexpr int _p<Acc, QueryType, Arg, Args...> = _p<Acc + 1, QueryType, Args...>; // recursive case
    
    ;

    template <int Acc, typename QueryType>
    constexpr int  _p<Acc, QueryType, QueryType> = Acc; // base case

    template <typename QueryType, typename... Args> 
    constexpr int packTypeToIndex = _p<0, QueryType, Args...>;
    





}



template <typename... Args>

struct Pack {
    constexpr static int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::_packIndexToType<QueryIndex,Args...>;

    template <typename QueryType> 
    constexpr static int index = pack_detail::packTypeToIndex<QueryType, Args...>;

};

#endif  // PACK_H
