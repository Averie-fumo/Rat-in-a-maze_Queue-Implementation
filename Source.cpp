#include <iostream>
#include "myconsole.h"
#include "mygraphics.h"
using namespace std;

template <typename T>
class queue
{
	class node
	{
	private:
		int x;
		int y;
		node* next;
		node* prev;
	public :
		friend class list;
		node()
		{
			next = nullptr;
			prev = nullptr;
		}
	};
	class list
	{
	private :
		node* head;
		node* tail;
		int size = 0;
		int xvalue, yvalue;
	public :
		list()
		{
			head = new node;
			tail = new node;
		}
		void insert_at_head(int x, int y)
		{
			if (head->x == NULL&& head->y==NULL)
			{
				head->x = x;
				head->y = y;
				head->next = nullptr;
				head->prev = nullptr;
				xvalue = head->x;
				yvalue = head->y;
			}
			else if (head->next == nullptr)
			{
				tail = head;
				head->x = x;
				head->y = y;
				head->next = tail;
				tail->prev = head;
				tail->next = nullptr;
				xvalue = tail->x;
				yvalue = tail->y;
			}
			else
			{
				node* n = new node;
				n->x = x;
				n-> y = y;
				n->next = head;
				head->prev = n;
				head = n;
				xvalue = tail->x;
				yvalue = tail->y;
			}
			size++;
		}
		void delete_at_tail()
		{
			xvalue = tail->x;
			yvalue = tail->y;
			node* temp = tail; 
			tail->prev = tail; 
			tail->next = nullptr;
			delete temp; 
			temp = nullptr;
			size--;
		}
		int getx()
		{
			return xvalue;
		}
		int gety()
		{
			return yvalue;
		}
		bool listEmpty()
		{
			if (size <= 0)
				return true;
			return false;
		}
	};
	list q;
public :
	friend class list;
	void enqueue(int x, int y)
	{
		q.insert_at_head(x, y);
	}
	void dequeue()
	{
		q.delete_at_tail();
	}
	bool isEmpty()
	{
		if (q.listEmpty()== true)
			return true;
		return false;
	}
	int getx()
	{
		return q.getx();
	}
	int gety()
	{
		return q .gety();
	}
};
void display_maze(int rows, int cols, int** maze)
{
	//clearscreen();
	//myrect(0, 0, rows * 50, cols * 50, rgb(0, 0, 0), rgb(255, 165, 0));
	int x = 0, y = 0;
	//for (int i = 0;i < rows;i++)
	//{
	//	x = 0;
	//	for (int j = 0;j < cols;j++)
	//	{
	//		if (maze[i][j] == 0)
	//		{
	//			myrect(x, y, x + 50, y + 50, rgb(0, 0, 0), rgb(255, 165, 0));
	//			x = x + 50;
	//		}
	//		else if (maze[i][j] == -1)
	//		{
	//			myrect(x, y, x + 50, y + 50, rgb(0, 0, 0), rgb(0, 0, 255));
	//			x = x + 50;

	//		}
	//		else
	//		{
	//			myrect(x, y, x + 50, y + 50, rgb(0, 0, 0), rgb(0, 255, 0));
	//			x = x + 50;
	//		}
	//	}
	//	y = y + 50;
	//}

	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			cout << maze[i][j] << "  ";
		}
		cout << endl;
	}

}
void place_rat_dest(int srcx, int srcy, int destx, int desty, int** maze)
{
	maze[srcx][srcy] = -2;
	maze[destx][desty] = -3;
}
void movement(int& srcx, int& srcy,int& destx,int& desty, int**maze, queue<int> q, int rows, int cols)
{
	int distance = -2;
	int x = 0, y = 0;
	bool found = false;
	bool empty = false;
	while (!found && !empty)
	{
		for (int i = 0;i < rows;i++)
		{
			for (int j = 0;j < cols;j++)
			{
				if (maze[i][j] == distance)
				{
					q.enqueue(i, j);
					cout << q.getx() << "." << q.gety() << endl;
				}
			}
		}
		if (distance == -2)
			distance = 0;
		distance++;
		while (!q.isEmpty())
		{
			q.dequeue();
			x = q.getx();
			y = q.gety();
			cout << endl << x << "," << y;
			if (x == destx && y == desty)
			{
				found = true;
				break;
			}

			if (x > 0)
				if (maze[x - 1][y] != -1)
				{
					maze[x - 1][y] = distance;
				}
			if (x < rows - 1)
				if (maze[x + 1][y] != -1)
				{
					maze[x + 1][y] = distance;
				}
			if (y > 0)
				if (maze[x][y - 1] != -1)
				{
					maze[x][y - 1] = distance;
				}
			if (y < cols - 1)
				if (maze[x][y + 1] != -1)
				{
					maze[x][y + 1] = distance;
				}
		}
		found = true;
	}
	cout << "found." << endl;
}

void take_maze( int** maze, int rows, int cols, int&srcx , int& srcy, int& destx ,int& desty)
{ 
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < cols;j++)
		{
			maze[i][j] = 0;
		}

	int k;
	for (int i = 0; i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			k = rand() % 10 + 1;
			if (k == 9 || k == 8)
			{
				maze[i][j] = -1;
			}
		}
	}
	//for (int i = 0, j = 0; j < cols;j++)
	//{
	//	maze[i][j] = '-';
	//}
	//for (int i = rows-1, j = 0; j < cols;j++)
	//{
	//	maze[i][j] = '-';

	//}
	//for (int i = 0, j = 0; i < rows;i++)
	//{
	//	maze[i][j] = '-';

	//}
	//for (int i = 0, j = cols-1; i < rows;i++)
	//{
	//	maze[i][j] = '-';
	//}
	cout << "Source X coordinate:" << endl;
	cin >> srcx;
	cout << "Source Y coordinate:" << endl;
	cin >> srcy;
	cout << "Destination X coordinate:" << endl;
	cin >> destx;
	cout << "Destination Y coordinate:" << endl;
	cin >> desty;
}

int main()
{
	//Maximized();
	int srcx = 0, srcy = 0, destx = 0, desty = 0, rows = 0, cols = 0;
	queue<int> q;
	cout << "Enter rows:" << endl;
	cin >> rows;
	cout << "Enter columns: " << endl;
	cin >> cols;
	int** maze = new int* [rows];
	for (int i = 0; i < rows;i++)
	{
		maze[i] = new int[cols];
	}
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			maze[i][j] = 0;
		}
	}
	take_maze(maze, rows, cols, srcx, srcy, destx, desty);

	place_rat_dest(srcx, srcy, destx, desty, maze);
	display_maze(rows, cols, maze);
	movement(srcx, srcy, destx, desty, maze, q, rows, cols);
	//PlaceCursor(0, rows + 4);
	for (int i = 0; i < rows;i++)
	{
		delete maze[i];
		maze[i] = nullptr;
	}
	delete maze;
	maze = nullptr;
	return 0;
}