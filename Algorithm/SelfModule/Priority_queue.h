#pragma once
#include <vector>


template <typename T, typename Container = std::vector<T>, typename Predicate = less<T>>
class Priority_queue
{
public:

	void push(const T& data)
	{
		// 힙 구조 맞춰주기
		_heap.push_back(data);
		// 순서 맞춰주기
		int now = static_cast<int>(_heap.size() - 1);
		//루트노드까지 순회
		while (now > 0)
		{
			int next = (now - 1) / 2;
			// 부모노드와 나와 비교
			/*
			if (_heap[next] > _heap[now])
			{
				break;
			}
			*/
			if (_predicate(_heap[now], _heap[next])) break;  // less 기준으로 왼쪽값이 작으면 true, 아니면 false 

			std::swap(_heap[next], _heap[now]);
			now = next;
		}
	}
	void pop()
	{
		// _heap[0] 제거
		// 가장 마지막 노드 올리기
		int last = _heap.size() - 1;
		_heap[0] = _heap[last];
		_heap.pop_back();
		// 밑에것들과 비교
		int now = 0;
		while (true)
		{
			int next = now;
			int left = (2 * now) + 1;
			int right = (2 * now) + 2;
			//끝에 도달할경우
			if (left >= _heap.size()) break;

			if (_predicate(_heap[next], _heap[left])) next = left;
			if (right < _heap.size() && _predicate(_heap[next], _heap[right])) next = right;
			if (now == next) break;
			std::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top()
	{
		return _heap[0];
	}
	bool empty()
	{
		return _heap.empty();
	}
private:
	Container _heap;
	Predicate _predicate;
};

