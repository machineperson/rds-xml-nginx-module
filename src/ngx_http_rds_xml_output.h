
/*
 * Copyright (C) agentzh
 */


#ifndef NGX_HTTP_RDS_XML_OUTPUT_H
#define NGX_HTTP_RDS_XML_OUTPUT_H


#include "ngx_http_rds_xml_filter_module.h"
#include "ngx_http_rds.h"

#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>


ngx_int_t ngx_http_rds_xml_output_header(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx, ngx_http_rds_header_t *header);
ngx_int_t ngx_http_rds_xml_output_cols(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx);
ngx_int_t ngx_http_rds_xml_output_literal(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx, u_char *data, size_t len, int last_buf);
ngx_int_t ngx_http_rds_xml_output_bufs(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx);
ngx_int_t ngx_http_rds_xml_output_field(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx, u_char *data, size_t len, int is_null);
ngx_int_t ngx_http_rds_xml_output_more_field_data(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx, u_char *data, size_t len);
ngx_int_t ngx_http_rds_xml_output_props(ngx_http_request_t *request,
    ngx_http_rds_xml_ctx_t *ctx, ngx_http_rds_xml_loc_conf_t *conf);


#endif /* NGX_HTTP_RDS_XML_OUTPUT_H */
