# assign a template
TEMPLATE = subdirs

#configure to build one by one in a order
CONFIG   += ordered

# add the subdirs for all the projects
SUBDIRS += \
        Networking \
        Ssh \
        Files \
        Api \
        Utils \
        System \
        Terminal \
        SerialPort \
        Sql \
        Media \
        Components

OTHER_FILES += \
        README.md
