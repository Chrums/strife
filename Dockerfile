FROM trzeci/emscripten:latest

ARG BOOST_VERSION=1.72.0
ARG BOOST_VERSION_=1_72_0
ENV BOOST_ROOT=/usr/include/boost
ENV BOOST_LIBRARIES=system,filesystem

RUN wget --max-redirect 3 https://dl.bintray.com/boostorg/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_}.tar.gz
RUN mkdir -p ${BOOST_ROOT} && tar zxf boost_${BOOST_VERSION_}.tar.gz -C ${BOOST_ROOT} --strip-components=1

RUN cd $BOOST_ROOT \
    && ./bootstrap.sh --with-libraries=${BOOST_LIBRARIES} \
    && ./b2 -a -j8 toolset=clang-emscripten link=static threading=single variant=release stage \
    && mkdir /usr/lib/boost \
    && cp stage/lib/*.a /usr/lib/boost \
    && rm -rf stage

ENTRYPOINT /bin/bash