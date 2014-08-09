TEMPLATE = subdirs

remotepath = /home/user/MultiMote/remotes/QDL

remote.files = remote.xml
remote.path = "$$remotepath"
settings.files = settings.xml
settings.path = "$$remotepath"
jscript.files += $$files(*.js)
jscript.path = "$$remotepath"

INSTALLS += remote settings jscript
