#ifndef ColQueue_h
#define ColQueue_h
class ColQueue{
private:
	int *data;
	int front, rear, num, length;
public:
	ColQueue(int N);
	void Enter(int a);
	int Get();
	int Length();
};
#endif

