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

		tuple(const Head& head, const Tail&... tail)
			: head{ head }
			, tail{ tail... }
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
		static auto apply(const tuple<Head, Tail...> t)
		{
			return tuple_get<N - 1>::apply(t.get_tail());
		}
	};

	template<>
	struct tuple_get<0>
	{
		template<typename Head, typename... Tail>
		static auto apply(const tuple<Head, Tail...> t)
		{
			return t.get_head();
		}
	};

	template<size_t N, typename... Types>
	auto get(const tuple<Types...>& t)
	{
		return tuple_get<N>::apply(t);
	}

} // namespace strike