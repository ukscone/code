enum Color {
	RED,
	BLUE,
	GREEN
};
enum Maker {
	CRASH,
	BOOM,
	BANG
};

class Car 
{
	public:
		Maker getMaker();
		Color getColor();
		void setColor(Color _color);
};
