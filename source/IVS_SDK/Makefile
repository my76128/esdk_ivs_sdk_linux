#                     MAKE MACRO DEFINATION

os = suse11
ROOT =..
PLATFORM = ../../../platform
OBJDIR  = $(ROOT)/IVS_SDK/obj
BINDIR	= $(ROOT)/IVS_SDK/build/linux
LIBDIR	= $(ROOT)/IVS_SDK/lib
ifeq ($(os),suse11)
LIBDIR2	= $(PLATFORM)/IVS_COMMON/CBB/release/new/linux
LIBDIR3	= $(PLATFORM)/IVS_BP/release/new/linux
else
LIBDIR2	= $(PLATFORM)/IVS_COMMON/CBB/release/new/linux/suse10
LIBDIR3	= $(PLATFORM)/IVS_BP/release/new/linux/suse10
endif
#LIBDIR4 = $(ROOT)/IVS_MP/build/linux
LIBDIR4 = $(ROOT)/IVS_Netsource/build/linux
LIBDIR5 = $(PLATFORM)/IVS_MP/IVS_MP_LINUX/release/new/linux

INCDIR  = $(ROOT)/IVS_SDK/inc
INCDIR2 = $(PLATFORM)/IVS_COMMON/inc
INCDIR3 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_alarm
INCDIR4 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_base
INCDIR5 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_compression
INCDIR6 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_http
INCDIR7 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_pcre
INCDIR8 = $(ROOT)/IVS_SDK/rtsp_client/header
INCDIR9 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_security
INCDIR10 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_sftp
INCDIR11 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ivs_sql
INCDIR12 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/xml
INCDIR13 = $(PLATFORM)/IVS_BP/release/new/header/bp_base
INCDIR14 = $(PLATFORM)/IVS_BP/release/new/header/bp_frame
INCDIR15 = $(PLATFORM)/IVS_BP/release/new/header/bp_log
INCDIR16 = $(PLATFORM)/IVS_BP/release/new/header/bp_monitor
INCDIR17 = $(PLATFORM)/IVS_BP/release/new/header/bp_msg_resend
INCDIR18 = $(PLATFORM)/IVS_BP/release/new/header/bp_net
INCDIR19 = $(PLATFORM)/IVS_BP/release/new/header/bp_protocol/bp_nss
INCDIR20 = $(PLATFORM)/IVS_BP/release/new/header/bp_sys
INCDIR21 = $(ROOT)/IVS_SDK/IVS_SDK/IVS/Sys
INCDIR22 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/libssh2/include
INCDIR23 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/openssl
INCDIR24 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/openssl/include
INCDIR25 = $(PLATFORM)/IVS_COMMON/CBB/release/new/header/ACE_wrappers
#INCDIR26 = $(ROOT)/IVS_MP/inc
INCDIR26 = $(ROOT)/IVS_Netsource/inc
INCDIR27 = $(PLATFORM)/IVS_MP/IVS_MP_LINUX/release/new/linux/header


RTSPDIR =  $(ROOT)/IVS_SDK/rtsp_client
SOURCEDIR0 = $(ROOT)/IVS_SDK/inc/common/BaseThread
SOURCEDIR1 = $(ROOT)/IVS_SDK/inc/common/log
SOURCEDIR2 = $(ROOT)/IVS_SDK/inc/common/Timer
SOURCEDIR3 = $(ROOT)/IVS_SDK/inc/common/ToolsHelp
SOURCEDIR4 = $(ROOT)/IVS_SDK/IVS_SDK/common
SOURCEDIR5 = $(ROOT)/IVS_SDK/IVS_SDK/IVS
SOURCEDIR6 = $(ROOT)/IVS_SDK/IVS_SDK/IVS/Sys
SOURCEDIR7 = $(ROOT)/IVS_SDK/IVS_SDK/service/AlarmLinkage
SOURCEDIR8 = $(ROOT)/IVS_SDK/IVS_SDK/service/AlarmMgr
SOURCEDIR9 = $(ROOT)/IVS_SDK/IVS_SDK/service/AutoResume
SOURCEDIR10 = $(ROOT)/IVS_SDK/IVS_SDK/service/CapturePicture
SOURCEDIR11 = $(ROOT)/IVS_SDK/IVS_SDK/service/ClientNetwork
SOURCEDIR12 = $(ROOT)/IVS_SDK/IVS_SDK/service/DevicMgr
SOURCEDIR13 = $(ROOT)/IVS_SDK/IVS_SDK/service/Download
SOURCEDIR14 = $(ROOT)/IVS_SDK/IVS_SDK/service/Event
SOURCEDIR15 = $(ROOT)/IVS_SDK/IVS_SDK/service/IntelligenceAnalysis
SOURCEDIR16 = $(ROOT)/IVS_SDK/IVS_SDK/service/Login
SOURCEDIR17 = $(ROOT)/IVS_SDK/IVS_SDK/service/LogMgr
SOURCEDIR18 = $(ROOT)/IVS_SDK/IVS_SDK/service/MotionDetecMgr
SOURCEDIR19 = $(ROOT)/IVS_SDK/IVS_SDK/service/NetKeyBoard
SOURCEDIR20 = $(ROOT)/IVS_SDK/IVS_SDK/service/PlayBack
SOURCEDIR21 = $(ROOT)/IVS_SDK/IVS_SDK/service/PtzControl
SOURCEDIR22 = $(ROOT)/IVS_SDK/IVS_SDK/service/RealPlay
SOURCEDIR23 = $(ROOT)/IVS_SDK/IVS_SDK/service/Record
SOURCEDIR24 = $(ROOT)/IVS_SDK/IVS_SDK/service/ReportMgr
SOURCEDIR25 = $(ROOT)/IVS_SDK/IVS_SDK/service/Telepresence
SOURCEDIR26 = $(ROOT)/IVS_SDK/IVS_SDK/service/TVWallMgr
SOURCEDIR27 = $(ROOT)/IVS_SDK/IVS_SDK/service/UserDataMgr
SOURCEDIR28 = $(ROOT)/IVS_SDK/IVS_SDK/service/UserInfoMgr
SOURCEDIR29 = $(ROOT)/IVS_SDK/IVS_SDK/service/Voice
SOURCEDIR30 = $(ROOT)/IVS_SDK/IVS_SDK
SOURCEDIR31 = $(ROOT)/IVS_SDK/inc/common
SOURCEDIR32 = $(ROOT)/IVS_SDK/IVS_SDK/service/UpgradeMgr

ver = debug
ifeq ($(ver),debug)
CCFlag =  -O -g -w -fPIC -c -fmessage-length=0
else
CCFlag =  -O2 -w -fPIC -c -fmessage-length=0
endif

CC = g++
LINK = g++
LINKFlag = -shared
PRJNAME = IVS_SDK
NODENAME := $(shell uname -n)

#GNU Make 3.80版本不支持ifeq else ifeq这种语法，SUSE10是GNU Make 3.80，SUSE11和Redhat5.4是GNU Make 3.81
ifeq (suse11, $(findstring suse11,$(NODENAME)))
  TARNAME = eSDK_IVS_API_V1.3.30_SUSE11'(64bit)'.tar.gz
else ifeq (suse10, $(findstring suse10,$(NODENAME)))
  TARNAME = eSDK_IVS_API_V1.3.30_SUSE10'(32bit)'.tar.gz
else ifeq (redhat54, $(findstring redhat54,$(NODENAME)))
  TARNAME = eSDK_IVS_API_V1.3.30_RedHat5.4'(32bit)'.tar.gz
endif

PROGRAM = lib$(PRJNAME).so

INCLUDES = -I$(SOURCEDIR0) -I$(SOURCEDIR1) -I$(SOURCEDIR2) -I$(SOURCEDIR3) -I$(SOURCEDIR4) \
-I$(SOURCEDIR5) -I$(SOURCEDIR6) -I$(SOURCEDIR7) -I$(SOURCEDIR8) -I$(SOURCEDIR9) -I$(SOURCEDIR10) \
-I$(SOURCEDIR11) -I$(SOURCEDIR12) -I$(SOURCEDIR13) -I$(SOURCEDIR14) -I$(SOURCEDIR15) -I$(SOURCEDIR16) \
-I$(SOURCEDIR17) -I$(SOURCEDIR18) -I$(SOURCEDIR19) -I$(SOURCEDIR20) -I$(SOURCEDIR21) -I$(SOURCEDIR22) \
-I$(SOURCEDIR23) -I$(SOURCEDIR24) -I$(SOURCEDIR25) -I$(SOURCEDIR26) -I$(SOURCEDIR27) -I$(SOURCEDIR28) \
-I$(SOURCEDIR29) -I$(SOURCEDIR30) -I$(SOURCEDIR31) -I$(SOURCEDIR32) -I$(INCDIR) -I$(INCDIR2) -I$(INCDIR3) \
-I$(INCDIR4) -I$(INCDIR5) -I$(INCDIR6) -I$(INCDIR7) -I$(INCDIR8) -I$(INCDIR9) -I$(INCDIR10) \
-I$(INCDIR11) -I$(INCDIR12) -I$(INCDIR13) -I$(INCDIR14) -I$(INCDIR15) -I$(INCDIR16) -I$(INCDIR17) -I$(INCDIR18) \
-I$(INCDIR19) -I$(INCDIR20) -I$(INCDIR21) -I$(INCDIR22) -I$(INCDIR23) -I$(INCDIR24) -I$(INCDIR25) \
-I$(INCDIR26) -I$(INCDIR27)



LIBDIRS = -L$(LIBDIR2) -L$(LIBDIR3) -L$(LIBDIR4) -L$(LIBDIR5)
LIBS = -lpthread -lBase -livs_sftp -lFrame -lNet -lNSS -lLog -livs_rtsp_client -lMsgResend -lIVS_Player -lIVS_NetSource

MACROS = -DUE_TERM_ROUTE -DDEBUG

RM = rm -f

#                       SOURCE FILES
SOURCE0 := $(wildcard $(SOURCEDIR0)/*.cpp)
OBJ0 := $(patsubst $(SOURCEDIR0)/%.cpp,$(OBJDIR)/%.o,$(SOURCE0))
SOURCE1 := $(wildcard $(SOURCEDIR1)/*.cpp)
OBJ1 := $(patsubst $(SOURCEDIR1)/%.cpp,$(OBJDIR)/%.o,$(SOURCE1))
SOURCE2 := $(wildcard $(SOURCEDIR2)/*.cpp)
OBJ2 := $(patsubst $(SOURCEDIR2)/%.cpp,$(OBJDIR)/%.o,$(SOURCE2))
SOURCE3 := $(wildcard $(SOURCEDIR3)/*.cpp)
OBJ3 := $(patsubst $(SOURCEDIR3)/%.cpp,$(OBJDIR)/%.o,$(SOURCE3))
SOURCE4 := $(wildcard $(SOURCEDIR4)/*.cpp)
OBJ4 := $(patsubst $(SOURCEDIR4)/%.cpp,$(OBJDIR)/%.o,$(SOURCE4))
SOURCE5 := $(wildcard $(SOURCEDIR5)/*.cpp)
OBJ5 := $(patsubst $(SOURCEDIR5)/%.cpp,$(OBJDIR)/%.o,$(SOURCE5))
SOURCE6 := $(wildcard $(SOURCEDIR6)/*.cpp)
OBJ6 := $(patsubst $(SOURCEDIR6)/%.cpp,$(OBJDIR)/%.o,$(SOURCE6))
SOURCE7 := $(wildcard $(SOURCEDIR7)/*.cpp)
OBJ7 := $(patsubst $(SOURCEDIR7)/%.cpp,$(OBJDIR)/%.o,$(SOURCE7))
SOURCE8 := $(wildcard $(SOURCEDIR8)/*.cpp)
OBJ8 := $(patsubst $(SOURCEDIR8)/%.cpp,$(OBJDIR)/%.o,$(SOURCE8))
SOURCE9 := $(wildcard $(SOURCEDIR9)/*.cpp)
OBJ9 := $(patsubst $(SOURCEDIR9)/%.cpp,$(OBJDIR)/%.o,$(SOURCE9))
SOURCE10 := $(wildcard $(SOURCEDIR10)/*.cpp)
OBJ10 := $(patsubst $(SOURCEDIR10)/%.cpp,$(OBJDIR)/%.o,$(SOURCE10))
SOURCE11 := $(wildcard $(SOURCEDIR11)/*.cpp)
OBJ11 := $(patsubst $(SOURCEDIR11)/%.cpp,$(OBJDIR)/%.o,$(SOURCE11))
SOURCE12 := $(wildcard $(SOURCEDIR12)/*.cpp)
OBJ12 := $(patsubst $(SOURCEDIR12)/%.cpp,$(OBJDIR)/%.o,$(SOURCE12))
SOURCE13 := $(wildcard $(SOURCEDIR13)/*.cpp)
OBJ13 := $(patsubst $(SOURCEDIR13)/%.cpp,$(OBJDIR)/%.o,$(SOURCE13))
SOURCE14 := $(wildcard $(SOURCEDIR14)/*.cpp)
OBJ14 := $(patsubst $(SOURCEDIR14)/%.cpp,$(OBJDIR)/%.o,$(SOURCE14))
SOURCE15 := $(wildcard $(SOURCEDIR15)/*.cpp)
OBJ15 := $(patsubst $(SOURCEDIR15)/%.cpp,$(OBJDIR)/%.o,$(SOURCE15))
SOURCE16 := $(wildcard $(SOURCEDIR16)/*.cpp)
OBJ16 := $(patsubst $(SOURCEDIR16)/%.cpp,$(OBJDIR)/%.o,$(SOURCE16))
SOURCE17 := $(wildcard $(SOURCEDIR17)/*.cpp)
OBJ17 := $(patsubst $(SOURCEDIR17)/%.cpp,$(OBJDIR)/%.o,$(SOURCE17))
SOURCE18 := $(wildcard $(SOURCEDIR18)/*.cpp)
OBJ18 := $(patsubst $(SOURCEDIR18)/%.cpp,$(OBJDIR)/%.o,$(SOURCE18))
SOURCE19 := $(wildcard $(SOURCEDIR19)/*.cpp)
OBJ19 := $(patsubst $(SOURCEDIR19)/%.cpp,$(OBJDIR)/%.o,$(SOURCE19))
SOURCE20 := $(wildcard $(SOURCEDIR20)/*.cpp)
OBJ20 := $(patsubst $(SOURCEDIR20)/%.cpp,$(OBJDIR)/%.o,$(SOURCE20))
SOURCE21 := $(wildcard $(SOURCEDIR21)/*.cpp)
OBJ21 := $(patsubst $(SOURCEDIR21)/%.cpp,$(OBJDIR)/%.o,$(SOURCE21))
SOURCE22 := $(wildcard $(SOURCEDIR22)/*.cpp)
OBJ22 := $(patsubst $(SOURCEDIR22)/%.cpp,$(OBJDIR)/%.o,$(SOURCE22))
SOURCE23 := $(wildcard $(SOURCEDIR23)/*.cpp)
OBJ23 := $(patsubst $(SOURCEDIR23)/%.cpp,$(OBJDIR)/%.o,$(SOURCE23))
SOURCE24 := $(wildcard $(SOURCEDIR24)/*.cpp)
OBJ24 := $(patsubst $(SOURCEDIR24)/%.cpp,$(OBJDIR)/%.o,$(SOURCE24))
SOURCE25 := $(wildcard $(SOURCEDIR25)/*.cpp)
OBJ25 := $(patsubst $(SOURCEDIR25)/%.cpp,$(OBJDIR)/%.o,$(SOURCE25))
SOURCE26 := $(wildcard $(SOURCEDIR26)/*.cpp)
OBJ26 := $(patsubst $(SOURCEDIR26)/%.cpp,$(OBJDIR)/%.o,$(SOURCE26))
SOURCE27 := $(wildcard $(SOURCEDIR27)/*.cpp)
OBJ27 := $(patsubst $(SOURCEDIR27)/%.cpp,$(OBJDIR)/%.o,$(SOURCE27))
SOURCE28 := $(wildcard $(SOURCEDIR28)/*.cpp)
OBJ28 := $(patsubst $(SOURCEDIR28)/%.cpp,$(OBJDIR)/%.o,$(SOURCE28))
SOURCE29 := $(wildcard $(SOURCEDIR29)/*.cpp)
OBJ29 := $(patsubst $(SOURCEDIR29)/%.cpp,$(OBJDIR)/%.o,$(SOURCE29))
SOURCE30 := $(wildcard $(SOURCEDIR30)/*.cpp)
OBJ30 := $(patsubst $(SOURCEDIR30)/%.cpp,$(OBJDIR)/%.o,$(SOURCE30))
SOURCE31 := $(wildcard $(SOURCEDIR31)/*.cpp)
OBJ31 := $(patsubst $(SOURCEDIR31)/%.cpp,$(OBJDIR)/%.o,$(SOURCE31))
SOURCE32 := $(wildcard $(SOURCEDIR32)/*.cpp)
OBJ32 := $(patsubst $(SOURCEDIR32)/%.cpp,$(OBJDIR)/%.o,$(SOURCE32))

OBJS := $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) \
	$(OBJ8) $(OBJ9) $(OBJ10) $(OBJ11) $(OBJ12) $(OBJ13) $(OBJ14) $(OBJ15) \
	$(OBJ16) $(OBJ17) $(OBJ18) $(OBJ19) $(OBJ20) $(OBJ21) $(OBJ22) $(OBJ23) \
	$(OBJ24) $(OBJ25) $(OBJ26) $(OBJ27) $(OBJ28) $(OBJ29) $(OBJ30) $(OBJ31) $(OBJ32)
all: $(PROGRAM)
$(PROGRAM):  $(OBJS)
	$(LINK) $(MACROS) -o $(PRJNAME)/$(PROGRAM) $(OBJS) $(LINKFlag) $(LIBS) $(LIBDIRS)
$(OBJ0): $(OBJDIR)/%.o : $(SOURCEDIR0)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@ 
$(OBJ1): $(OBJDIR)/%.o : $(SOURCEDIR1)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ2): $(OBJDIR)/%.o : $(SOURCEDIR2)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@	
$(OBJ3): $(OBJDIR)/%.o : $(SOURCEDIR3)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ4): $(OBJDIR)/%.o : $(SOURCEDIR4)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ5): $(OBJDIR)/%.o : $(SOURCEDIR5)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ6): $(OBJDIR)/%.o : $(SOURCEDIR6)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ7): $(OBJDIR)/%.o : $(SOURCEDIR7)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ8): $(OBJDIR)/%.o : $(SOURCEDIR8)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@ 
$(OBJ9): $(OBJDIR)/%.o : $(SOURCEDIR9)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ10): $(OBJDIR)/%.o : $(SOURCEDIR10)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@	
$(OBJ11): $(OBJDIR)/%.o : $(SOURCEDIR11)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ12): $(OBJDIR)/%.o : $(SOURCEDIR12)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ13): $(OBJDIR)/%.o : $(SOURCEDIR13)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ14): $(OBJDIR)/%.o : $(SOURCEDIR14)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ15): $(OBJDIR)/%.o : $(SOURCEDIR15)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ16): $(OBJDIR)/%.o : $(SOURCEDIR16)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@ 
$(OBJ17): $(OBJDIR)/%.o : $(SOURCEDIR17)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ18): $(OBJDIR)/%.o : $(SOURCEDIR18)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@	
$(OBJ19): $(OBJDIR)/%.o : $(SOURCEDIR19)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ20): $(OBJDIR)/%.o : $(SOURCEDIR20)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ21): $(OBJDIR)/%.o : $(SOURCEDIR21)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ22): $(OBJDIR)/%.o : $(SOURCEDIR22)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ23): $(OBJDIR)/%.o : $(SOURCEDIR23)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ24): $(OBJDIR)/%.o : $(SOURCEDIR24)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@ 
$(OBJ25): $(OBJDIR)/%.o : $(SOURCEDIR25)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ26): $(OBJDIR)/%.o : $(SOURCEDIR26)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@	
$(OBJ27): $(OBJDIR)/%.o : $(SOURCEDIR27)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ28): $(OBJDIR)/%.o : $(SOURCEDIR28)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ29): $(OBJDIR)/%.o : $(SOURCEDIR29)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ30): $(OBJDIR)/%.o : $(SOURCEDIR30)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ31): $(OBJDIR)/%.o : $(SOURCEDIR31)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
$(OBJ32): $(OBJDIR)/%.o : $(SOURCEDIR32)/%.cpp
	$(CC) -c $(MACROS) $(CCFlag) $(INCLUDES) $< -o $@
	
clean::
	$(RM) $(OBJDIR)/*
	$(RM) $(ROOT)/IVS_SDK/IVS_SDK/libIVS_SDK.so
	
#	$(RM) $(BINDIR)/*
cleanpart::
	$(RM) $(OBJDIR)/*.o
dep: delete_previous_depend $(OBJS:%.o=%_dep)
delete_previous_depend:
	$(RM) -f depend
$(OBJ0:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR0)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ1:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR1)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ2:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR2)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ3:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR3)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ4:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR4)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ5:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR5)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ6:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR6)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ7:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR7)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ8:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR8)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ9:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR9)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ10:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR10)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ11:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR11)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ12:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR12)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ13:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR13)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ14:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR14)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ15:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR15)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ16:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR16)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ17:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR17)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ18:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR18)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ19:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR19)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ20:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR20)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ21:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR21)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ22:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR22)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ23:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR23)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ24:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR24)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ25:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR25)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ26:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR26)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ27:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR27)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ28:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR28)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ29:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR29)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ30:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR30)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ31:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR31)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
$(OBJ32:%.o=%_dep): $(OBJDIR)/%_dep : $(SOURCEDIR32)/%.cpp
	$(CC) -MM  -MT '$(OBJDIR)/$*.o' $(CCFlag) $< $(INCLUDES) >>depend
	
-include depend 

tar:
#clear
	rm -rf $(BINDIR)/inc
	rm -rf $(BINDIR)/lib
	rm -rf $(BINDIR)/lib/protocols
#mkdir inc and lib
	mkdir $(BINDIR)/inc
	mkdir $(BINDIR)/lib
	mkdir $(BINDIR)/lib/protocols
#copy *.h	
	cp $(PLATFORM)/IVS_COMMON/inc/hwsdk.h $(BINDIR)/inc/
	cp $(PLATFORM)/IVS_COMMON/inc/ivs_error.h $(BINDIR)/inc/
	cp $(ROOT)/IVS_SDK/build/linux/IVS_SDK.h $(BINDIR)/inc/
#copy libIVS_SDK.so
	cp $(ROOT)/IVS_SDK/IVS_SDK/libIVS_SDK.so $(BINDIR)/lib/
#copy libIVS_Player.so
	cp $(PLATFORM)/IVS_MP/IVS_MP_LINUX/release/new/linux/libIVS_Player.so $(BINDIR)/lib/
#copy libIVS_NetSource.so
	cp $(ROOT)/IVS_Netsource/build/linux/libIVS_NetSource.so $(BINDIR)/lib/
#copy IVS_COMMON/release/new/linux/*.so
	cp $(LIBDIR2)/*.so $(BINDIR)/lib/
	cp $(LIBDIR2)/*.so.* $(BINDIR)/lib/
#删掉不需要的libociei.so和libssh2.so.1.0
	rm -f $(BINDIR)/lib/libociei.so
	rm -f $(BINDIR)/lib/libssh2.so.1.0
#copy IVS_BP/release/new/linux/*.so
	cp $(LIBDIR3)/*.so $(BINDIR)/lib/
	cp $(LIBDIR3)/libNSS.so $(BINDIR)/lib/protocols
#tar zip
	dos2unix $(BINDIR)/inc/*.h
	cd $(BINDIR); pwd; tar -zcvf $(TARNAME) inc lib config
install:tar
	cp $(BINDIR)/inc/*.h $(ROOT)/IVS_Demo/inc
	cp $(BINDIR)/lib/*.so* $(ROOT)/IVS_Demo/lib
	cp $(BINDIR)/lib/protocols/libNSS.so $(ROOT)/IVS_Demo/lib/protocols
	cp $(ROOT)/IVS_SDK/IVS_SDK/libIVS_SDK.so $(ROOT)/IVS_Demo/lib
copy:
	cp $(ROOT)/IVS_SDK/libIVS_SDK.so $(BINDIR)/lib/
	cp $(ROOT)/IVS_SDK/libIVS_SDK.so $(ROOT)/IVS_Demo/lib/