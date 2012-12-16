#pragma once

#include <string>

namespace zefiro{
namespace graphics{
class Font{
public:
	Font( int size = 16 , ::std::string name ="ＭＳ 明朝" , int weight = 300 , bool isItalic = false , bool isUnderLine = false , bool isStrikeOut = false , int quality =DEFAULT_QUALITY )
		:size_(size),name_(name),weight_(weight),isItalic_(isItalic),isUnderLine_(isUnderLine),isStrikeOut_(isStrikeOut),quality_(quality){

		LOGFONT *pLogFont = NULL;       //フォント情報
        LOGFONT logfont;
        logfont.lfHeight         = size;                       //ポイント
        logfont.lfWidth          = size/4;                           //幅（０：だと自動設定）
        logfont.lfEscapement     = 0;                           //テキスト行の描画角度
        logfont.lfOrientation    = 0;                           //ベースラインの角度
        logfont.lfWeight         = weight; //文字の太さ（400:標準 700:太字）
        logfont.lfItalic         = isItalic;  //斜体指定
        logfont.lfUnderline      = isUnderLine;//下線付き指定
        logfont.lfStrikeOut      = isStrikeOut;//打ち消し線指定
        logfont.lfCharSet        = SHIFTJIS_CHARSET;            //文字セット指定
        logfont.lfOutPrecision   = OUT_DEFAULT_PRECIS;          //フォントの出力精度指定
        logfont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;         //クリッピング精度指定 
		logfont.lfQuality        = quality;//フォントの出力品質指定
        logfont.lfPitchAndFamily = DEFAULT_PITCH;               //フォントのピッチ指定
        strcpy(logfont.lfFaceName,name.c_str());             //フォントの書体名指定
        //ポインタを設定
        pLogFont = &logfont;
        hFont_ = CreateFontIndirect(pLogFont);           	
	}
	virtual ~Font(){
		DeleteObject(hFont_);
	}
	int getQuality() const{
		return quality_;
	}
	int getSize() const{
		return size_;
	}
	::std::string getName() const{
		return name_;
	}
	/// 文字の太さ						(300:FW_LIGHT) , FW_BOLDは700
	int getWeight()const{
		return weight_;
	}
	bool isItalic()const{
		return isItalic_;
	}
	bool isUnderLine()const{
		return isUnderLine_;
	}
	// 打ち消し線
	bool isStrikeOut()const{
		return isStrikeOut_;
	}
	HFONT getHFont()const{
		return hFont_;
	}
private:
	HFONT hFont_;
	int quality_;
	int size_;
	int weight_;
	::std::string name_;
	bool isItalic_;
	bool isUnderLine_;
	bool isStrikeOut_;
};
}
}