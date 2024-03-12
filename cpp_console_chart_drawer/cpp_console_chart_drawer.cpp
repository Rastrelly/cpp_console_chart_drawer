#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct point 
{
	float x, y;
};

float func(int v, float x, float a, float f)
{
	switch (v)
	{
	default:
	case 1:
	{
		return a*x+f; 
		break;
	}
	case 2:
	{
		return a * pow(x, 2) + f;
		break;
	}
	case 3:
	{
		return a * sin(f*x);
		break;
	}
	}
}

int main()
{
	//variables
	float x1, x2, step, a, f;
	int ny, funcVar;
	std::vector<point> coords = {};

	while (true)
	{
		//get user inputs
		std::cout << "Select function: \n 1 - Linear; 2 - Quadratic; 3 - Sinusoidal\n";
		std::cin >> funcVar;
		std::cout << "Input a, f, x1, x2, step, ny:\n";
		std::cin >> a >> f >> x1 >> x2 >> step >> ny;

		//calculate function
		float cx = x1;
		coords.clear();
		while (cx <= x2)
		{
			point cpoint = { cx,func(funcVar,cx,a,f) };

			/*
			point cpoint;
			cpoint.x = cx;
			cpoint.y = func(cx, a, f);
			*/

			coords.push_back(cpoint);

			cx += step;
		}

		//print function
		int l = coords.size();
		for (int i = 0; i < l; i++)
		{
			std::cout << i + 1 << ") " << coords[i].x << "; " << coords[i].y << "\n";
		}

		//find ymin, ymax
		float ymin = coords[0].y;
		float ymax = coords[0].y;
		for (point cp : coords)
		{
			if (cp.y > ymax) ymax = cp.y;
			if (cp.y < ymin) ymin = cp.y;
		}

		//text renderer :D
		float deltax = coords[1].x - coords[0].x;
		int elems = coords.size();
		float deltay = (ymax - ymin) / (float)ny;

		std::ofstream filePrinter("outp.txt",std::ios::out|std::ios::app);

		filePrinter << "Chart received: \n";
		for (int j = 0; j < ny; j++)
		{
			for (int i = 0; i < elems - 1; i++)
			{
				float srcX = (coords[i].x + coords[i + 1].x) / 2;
				float srcY = (coords[i].y + coords[i + 1].y) / 2;
				float trgYmx = ymax - deltay * j;
				float trgYmn = ymax - deltay * (j + 1);
				if ((srcY < trgYmx) && (srcY > trgYmn))
				{
					std::cout << 'X';
					filePrinter << 'X';
				}
				else
				{
					std::cout << ' ';
					filePrinter << ' ';
				}
			}
			std::cout << "\n";
			filePrinter << "\n";
		}
		filePrinter.close();

		std::cout << "Exit program? [Y/N]\n";
		std::string resp;
		std::cin >> resp;
		if ((resp == "Y") || (resp == "y"))
		{
			break;
		}
	}
	system("pause");
}