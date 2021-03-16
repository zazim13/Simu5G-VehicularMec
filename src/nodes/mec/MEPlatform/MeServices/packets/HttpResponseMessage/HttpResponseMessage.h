/**
 * @author Alessandro Noferi
 *
 * This class create and manages HTTP responses packets, i.e.:
 *
 * HTTP/1.1 STATUS \r\n
 * headers[] \r\n
 * \r\n
 * body
 *
 *
 * The required headers for our scope are:
 * - Content-Type
 * - Connection
 * They are managed by specific setters and getters.
 * It is also possible add other headers via generic method (setHeaderField)
 *
 */

#ifndef _HTTRESPONSEMESSAGE_H_
#define  _HTTRESPONSEMESSAGE_H_



#include <omnetpp.h>
#include <string>
#include "nodes/mec/MEPlatform/MeServices/packets/HttpMessages_m.h"

#include "nodes/mec/MEPlatform/MeServices/packets/response/HttpResponsePacket.h"

//enum responseCode { OK,         // 200
//                    CREATED,    // 201
//                    NO_CONTENT, // 204
//                    BAD_REQ,    // 400
//                    UNAUTH,     // 401
//                    FORBIDDEN,  // 403
//                    NOT_FOUND,  // 404
//                    NOT_ACC,    // 406
//                    TOO_REQS,   // 429
//                    BAD_METHOD, // 405
//                    HTTP_NOT_SUPPORTED, // 505
//                    SERV_UNAV    //503
//                  };


/**
 * in HttpResponseMessage_m
 * {
 *     \@customize(true);
 *     string status;
 *     string connection;
 *     string contentType;
 *     string body;
 *     string payload;
 * }
 */

class HttpResponseMessage : public HttpResponseMessage_m
{
    public:
        HttpResponseMessage(const char *name=nullptr, short kind=0);
        HttpResponseMessage(const responseCode res, const char *name=nullptr, short kind=0);
        HttpResponseMessage& operator=(const HttpResponseMessage& other){if (this==&other) return *this; HttpResponseMessage_m::operator=(other); copy(other); return *this;}

        virtual HttpResponseMessage *dup() const override {return new HttpResponseMessage(*this);}

        virtual void addBodyChunk(const std::string& bodyChunk);
        // key MUST be like "key: "
        virtual void setHeaderField(const std::string& key, const std::string& value);

        virtual void setStatus(responseCode code);
        virtual void setStatus(const char* status) override;
        virtual std::string getPayload() const;
    private:
          void copy(const HttpResponseMessage& other);
          std::map<std::string, std::string> headerFields_;

};

#endif //_HTTRESPONSEMESSAGE_H_
