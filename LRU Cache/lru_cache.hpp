#ifndef _LRUCACHE_HPP_INCLUDED_
#define	_LRUCACHE_HPP_INCLUDED_

#include <unordered_map>
#include <list>

namespace NeonLost
{
	template<typename key_type, typename value_type>
	class lru_cache
	{
	private:
		typedef typename std::pair<key_type, value_type> key_value_pair;
		typedef typename std::list<key_value_pair>::iterator list_iterator;

		std::list<key_value_pair> cache_list;
		std::unordered_map<key_type, list_iterator> cache_map;
		size_t max_size;

	public:

		lru_cache(size_t max_size) : max_size(max_size) { }

		void put(const key_type& key, const value_type& value)
		{
			auto it = cache_map.find(key);

			if (it != cache_map.end())
			{
				cache_list.erase(it->second);
				cache_map.erase(it);
			}

			cache_list.push_front(key_value_pair(key, value));
			cache_map[key] = cache_list.begin();

			if (cache_map.size() > max_size)
			{
				auto last = cache_list.end();
				last--;
				cache_map.erase(last->first);
				cache_list.pop_back();
			}
		}

		const value_type& get_value(const key_type& key)
		{
			auto it = cache_map.find(key);

			if (it == cache_map.end())
			{
				throw std::range_error("chache do not containts this key");
			}
			else
			{
				cache_list.splice(cache_list.begin(), cache_list, it->second);
				return it->second->second;
			}
		}

		bool containts(const key_type& key) const
		{
			return cache_map.find(key) != cache_map.end();
		}

		size_t size() const
		{
			return cache_map.size();
		}
	};
}

#endif