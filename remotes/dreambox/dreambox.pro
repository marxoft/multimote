TEMPLATE = subdirs

remotepath = /home/user/MultiMote/remotes/DreamBox

remote.files = remote.xml
remote.path = "$$remotepath"
settings.files = settings.xml
settings.path = "$$remotepath"
jscript.files += remote.js
jscript.path = "$$remotepath"

INSTALLS += remote settings jscript
