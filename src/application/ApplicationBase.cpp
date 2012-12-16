#include "application/ApplicationBase.h"

namespace zefiro{
namespace application{
void ApplicationBase::run(){
	{
		ApplicationBases& abs = SingleApplicationBases::Instance();
		abs.add(this);
	}
	try{
		preCreate();
		getWindow()->create();
		postCreate();
		getWindow()->update();
		doRun();
		PostQuitMessage(0);
		pumpMessage(false);
		postDestory();
	}catch( zefiro::std::Exception &e ){
		::zefiro::std::win32debug_console_stream wdcon;
		wdcon << e.fileName() << " " << e.lineNumber()<< " " << e.what() << ::std::endl;			
	}
	{
		ApplicationBases& abs = SingleApplicationBases::Instance();
		abs.del();
	}
}

void ApplicationBase::doRun(){
}

}
}