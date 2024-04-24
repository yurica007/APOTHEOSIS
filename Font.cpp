#include "Font.h"
#include <DxLib.h>

constexpr int kTitleFontSize = 100;
constexpr int kCommentFontSize = 25;
constexpr int kMenuFontSize = 50;
constexpr int kOperateFontSize = 25;
constexpr int kResultFontSize = 100;

void Font::Load()
{
	titleFont = CreateFontToHandle(NULL, kTitleFontSize, -1, DX_FONTTYPE_NORMAL);
	commentFont = CreateFontToHandle(NULL, kCommentFontSize, -1, DX_FONTTYPE_NORMAL);
	menuFont = CreateFontToHandle(NULL, kMenuFontSize, -1, DX_FONTTYPE_NORMAL);
	operateFont = CreateFontToHandle(NULL, kOperateFontSize, -1, DX_FONTTYPE_NORMAL);
	resultFont = CreateFontToHandle(NULL, kResultFontSize, -1, DX_FONTTYPE_NORMAL);
}

void Font::Delete()
{
	DeleteFontToHandle(titleFont);
	DeleteFontToHandle(commentFont);
	DeleteFontToHandle(menuFont);
	DeleteFontToHandle(operateFont);
	DeleteFontToHandle(resultFont);
}

void Font::SetFontType(FontType fontType)
{
	switch (fontType)
	{
	case FontType::title:
		fontHandle = titleFont;
		fontSize = kTitleFontSize;
		break;
	case FontType::comment:
		fontHandle = commentFont;
		fontSize = kCommentFontSize;
		break;
	case FontType::menu:
		fontHandle = menuFont;
		fontSize = kMenuFontSize;
		break;
	case FontType::operate:
		fontHandle = operateFont;
		fontSize = kOperateFontSize;
		break;
	case FontType::result:
		fontHandle = resultFont;
		fontSize = kResultFontSize;
		break;
	}
}

int Font::GetFontType()
{
	return fontHandle;
}

int Font::GetFontSize()
{
	return fontSize / 2;
}
