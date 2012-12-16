#pragma once

#include <string>

namespace zefiro{
namespace graphics{
class Font{
public:
	Font( int size = 16 , ::std::string name ="�l�r ����" , int weight = 300 , bool isItalic = false , bool isUnderLine = false , bool isStrikeOut = false , int quality =DEFAULT_QUALITY )
		:size_(size),name_(name),weight_(weight),isItalic_(isItalic),isUnderLine_(isUnderLine),isStrikeOut_(isStrikeOut),quality_(quality){

		LOGFONT *pLogFont = NULL;       //�t�H���g���
        LOGFONT logfont;
        logfont.lfHeight         = size;                       //�|�C���g
        logfont.lfWidth          = size/4;                           //���i�O�F���Ǝ����ݒ�j
        logfont.lfEscapement     = 0;                           //�e�L�X�g�s�̕`��p�x
        logfont.lfOrientation    = 0;                           //�x�[�X���C���̊p�x
        logfont.lfWeight         = weight; //�����̑����i400:�W�� 700:�����j
        logfont.lfItalic         = isItalic;  //�Α̎w��
        logfont.lfUnderline      = isUnderLine;//�����t���w��
        logfont.lfStrikeOut      = isStrikeOut;//�ł��������w��
        logfont.lfCharSet        = SHIFTJIS_CHARSET;            //�����Z�b�g�w��
        logfont.lfOutPrecision   = OUT_DEFAULT_PRECIS;          //�t�H���g�̏o�͐��x�w��
        logfont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;         //�N���b�s���O���x�w�� 
		logfont.lfQuality        = quality;//�t�H���g�̏o�͕i���w��
        logfont.lfPitchAndFamily = DEFAULT_PITCH;               //�t�H���g�̃s�b�`�w��
        strcpy(logfont.lfFaceName,name.c_str());             //�t�H���g�̏��̖��w��
        //�|�C���^��ݒ�
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
	/// �����̑���						(300:FW_LIGHT) , FW_BOLD��700
	int getWeight()const{
		return weight_;
	}
	bool isItalic()const{
		return isItalic_;
	}
	bool isUnderLine()const{
		return isUnderLine_;
	}
	// �ł�������
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