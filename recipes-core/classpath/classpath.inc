DESCRIPTION = "GNU Classpath standard Java libraries"
HOMEPAGE = "http://www.gnu.org/software/classpath/"
SECTION = "libs"

# GPLv2 + custom linking exception
LICENSE = "Classpath"

PBN = "classpath"

inherit autotools java

DEPENDS = "virtual/javac-native fastjar-native zip-native gettext-native gmp antlr-native gtk+ gconf libxtst"

RPROVIDES_${PN} = ""

RDEPENDS_${PN} = "${PBN}-common (>= ${PV})"
RDEPENDS_${PN}-examples = "java2-runtime ${PN}-awt"
RDEPENDS_${PN}-tools = "java2-runtime"

RPROVIDES_${PN} = "${PBN}"
RPROVIDES_${PN}-common = "${PBN}-common"
RPROVIDES_${PN}-gtk = "${PBN}-awt"

PR = "r1"

SRC_URI = "${GNU_MIRROR}/classpath/classpath-${PV}.tar.gz"

S = "${WORKDIR}/${PBN}-${PV}"

export JAVA = "java"

EXTRA_OECONF = "\
  --with-glibj \
  --with-ecj=javac \
  --with-fastjar=fastjar \
  --includedir=${includedir}/classpath \
  --with-vm=java \
  --disable-Werror \
  --with-antlr-jar=${STAGING_DATADIR_JAVA_NATIVE}/antlr.jar \
  --disable-alsa \
  --disable-dssi \
  --disable-qt4-peer \
  --disable-plugin \
  --enable-gconf-peer \
  --enable-gtk-peer \
  --enable-local-sockets \
  --with-vm=java \
  "


EXTRA_OECONF += "\
               "

do_configure_prepend () {
  cp ${STAGING_DATADIR_NATIVE}/gettext/config.rpath ${S}
}
	

do_install() {
	autotools_do_install
	mv ${D}${libdir}/security ${D}${libdir}/${PBN}
}

# We really have valid non-symlink .so files
INSANE_SKIP_${PN} = "dev-so"

# Defines the packages that this classpath recipe creates.
# This allows the classpath-minimal variants to override this
# again.
CPPACKAGES = "${PBN}-common ${PN}-examples \
             ${PN}-tools ${PN}-tools-doc \
             ${PN}-gtk ${PN}-gconf"

PACKAGES =+ "${CPPACKAGES}"

FILES_${PN}-dev += "${libdir}/${PBN}/*.la ${incdir}/${PBN}"

FILES_${PBN}-common = "${datadir}/${PBN}/glibj.zip ${libdir}/logging.properties ${libdir}/${PBN}/security"
FILES_${PN}-examples = "${datadir}/${PBN}/examples"

FILES_${PN}-tools = "${datadir}/${PBN}/tools.zip ${bindir}"
FILES_${PN}-tools-doc = "${mandir}"

FILES_${PN}-dbg += "${libdir}/${PBN}/.debug"
FILES_${PN}-doc = "${infodir}"

# gcjwebplugin - not built yet
#FILES_${PN}-gcjwebplugin = "${libdir}/${PBN}/libgcjwebplugin.so"
FILES_${PN}-gtk = "${libdir}/${PBN}/libgtkpeer.so ${libdir}/${PBN}/libjawt.so"
FILES_${PN}-gconf = "${libdir}/${PBN}/libgconfpeer.so"
FILES_${PN} = "${libdir}/${PBN}/lib*so*"

