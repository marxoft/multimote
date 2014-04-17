TEMPLATE = subdirs

remotepath = /home/user/MultiMote/remotes/VLC

remote.files = remote.xml
remote.path = "$$remotepath"
settings.files = settings.xml
settings.path = "$$remotepath"
jscript.files = remote.js
jscript.path = "$$remotepath"
icon.files = vlc.png
icon.path = "$$remotepath"

INSTALLS += remote settings jscript icon
