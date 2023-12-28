#pragma once
#include <vector>


template <typename T, typename Container = std::vector<T>, typename Predicate = less<T>>
class Priority_queue
{
public:

	void push(const T& data)
	{
		// �� ���� �����ֱ�
		_heap.push_back(data);
		// ���� �����ֱ�
		int now = static_cast<int>(_heap.size() - 1);
		//��Ʈ������ ��ȸ
		while (now > 0)
		{
			int next = (now - 1) / 2;
			// �θ���� ���� ��
			/*
			if (_heap[next] > _heap[now])
			{
				break;
			}
			*/
			if (_predicate(_heap[now], _heap[next])) break;  // less �������� ���ʰ��� ������ true, �ƴϸ� false 

			std::swap(_heap[next], _heap[now]);
			now = next;
		}
	}
	void pop()
	{
		// _heap[0] ����
		// ���� ������ ��� �ø���
		int last = _heap.size() - 1;
		_heap[0] = _heap[last];
		_heap.pop_back();
		// �ؿ��͵�� ��
		int now = 0;
		while (true)
		{
			int next = now;
			int left = (2 * now) + 1;
			int right = (2 * now) + 2;
			//���� �����Ұ��
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

