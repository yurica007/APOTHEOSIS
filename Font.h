#pragma once

enum class FontType
{
	title,
	comment,
	menu,
	operate,
	result
};

class Font
{
public:
	Font() {}
	~Font() {}

	void Load();
	void Delete();
	void SetFontType(FontType fontType);
	int GetFontType();
	int GetFontSize();

private:
	int titleFont = 0;
	int commentFont = 0;
	int menuFont = 0;
	int operateFont = 0;
	int resultFont = 0;
	int fontSize = 0;

	int fontHandle = 0;
};

