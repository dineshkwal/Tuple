#pragma once

namespace strike
{
	template<typename... Types>
	class tuple;

	template<typename Head, typename... Tail>
	class tuple<Head, Tail...>
	{
	private:
		// storage
		Head head;
		tuple<Tail...> tail;

	public:
		// constructors
		tuple() = default;

		tuple(const Head& head, const tuple<Tail...>& tail)
			: head{ head }
			, tail{ tail }
		{
		}

		template<typename T, typename... Ts,
			typename = std::enable_if_t<sizeof...(Ts) == sizeof...(Tail)>>
		tuple(T&& t, Ts&&... ts)
			: head{ std::forward<T>(t) }
			, tail{ std::forward<Ts>(ts)... }
		{
		}

		// copy constructor
		template<typename T, typename... Ts,
			typename = std::enable_if_t<sizeof...(Ts) == sizeof...(Tail)>>
		tuple(const tuple<T, Ts...>& other)
			: head{ other.get_head() }
			, tail{ other.get_tail() }
		{
		}

		Head& get_head() { return head; }
		const Head& get_head() const { return head; }

		tuple<Tail...>& get_tail() { return tail; }
		const tuple<Tail...>& get_tail() const { return tail; }
	};

	// base case
	template<>
	class tuple<>
	{
		// no storage required
	};

	/************************************************************/

	template<size_t N>
	struct tuple_get
	{
		template<typename Head, typename... Tail>
		static auto apply(const tuple<Head, Tail...>& t)
		{
			return tuple_get<N - 1>::apply(t.get_tail());
		}
	};

	template<>
	struct tuple_get<0>
	{
		template<typename Head, typename... Tail>
		static auto apply(const tuple<Head, Tail...>& t)
		{
			return t.get_head();
		}
	};

	template<size_t N, typename... Types>
	auto get(const tuple<Types...>& t)
	{
		return tuple_get<N>::apply(t);
	}

	/************************************************************/

	template<typename... Types>
	auto make_tuple(Types&&... elems)
	{
		return tuple<std::decay_t<Types>...>(std::forward<Types>(elems)...);
	}

	/************************************************************/

} // namespace strike