TEMPLATE = subdirs

SUBDIRS += \
    src \
    example \
    designerplugin
    
example.depends = src
designerplugin.depends = src
