
/*
 * Copyright (C) agentzh
 */

#ifndef NGX_HTTP_RDS_XML_FILTER_MODULE_H
#define NGX_HTTP_RDS_XML_FILTER_MODULE_H

#include "ngx_http_rds.h"

#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>
#include <stdint.h>


#ifndef NGX_HTTP_RESET_CONTENT
#define NGX_HTTP_RESET_CONTENT 205
#endif


extern ngx_module_t  ngx_http_rds_xml_filter_module;

extern ngx_http_output_header_filter_pt  ngx_http_rds_xml_next_header_filter;

extern ngx_http_output_body_filter_pt    ngx_http_rds_xml_next_body_filter;

/* normal: <row> <column>value</column> </row>
 * compact: <row> <column_name /> </row> <row> <value /> </row> 
 * (that is the first row holds the column names)
 * (TODO: do we even want this)
 * pretty: does not do anything, TODO: figure out whether we need this 
 * */
typedef enum {
    xml_format_normal,
    xml_format_compact,
    xml_format_pretty          /* TODO */

} ngx_http_rds_xml_format_t;


typedef struct {
    ngx_str_t                       key;
    ngx_http_complex_value_t        value;
} ngx_http_rds_xml_property_t;


typedef struct {
    unsigned            requires_filters; /* :1 */

} ngx_http_rds_xml_main_conf_t;


typedef struct {
    ngx_flag_t                       enabled;
    ngx_uint_t                       format;
    ngx_str_t                        content_type;
    ngx_str_t                        root; /* rds_xml_root key */
    ngx_str_t                        success; /* rds_xml_success_property
                                               * key */
    ngx_array_t                     *user_props; /* rds_xml_user_property */

    ngx_str_t                        errcode_key;
    ngx_str_t                        errstr_key;

    size_t                           buf_size;

    /* for rds_xml_ret */
    ngx_str_t                        errcode;
    ngx_http_complex_value_t        *errstr;

} ngx_http_rds_xml_loc_conf_t;


typedef enum {
    state_expect_header,
    state_expect_col,
    state_expect_row,
    state_expect_field,
    state_expect_more_field_data,
    state_done

} ngx_http_rds_xml_state_t;


typedef struct {
    ngx_http_rds_xml_state_t            state;

    ngx_str_t                           *col_name;
    ngx_uint_t                           col_count;
    ngx_uint_t                           cur_col;

    ngx_http_rds_column_t               *cols;
    size_t                               row;

    uint32_t                             field_offset;
    uint32_t                             field_total;

    ngx_buf_tag_t                        tag;

    ngx_chain_t                         *out;
    ngx_chain_t                        **last_out;
    ngx_chain_t                         *busy_bufs;
    ngx_chain_t                         *free_bufs;

    ngx_buf_t                           *out_buf;
    ngx_buf_t                            cached;
    ngx_buf_t                            postponed;

    size_t                               avail_out;

    uint32_t                             field_data_rest;

    ngx_flag_t                           header_sent:1;
    ngx_flag_t                           seen_stream_end:1;
    ngx_flag_t                           generated_col_names:1;
} ngx_http_rds_xml_ctx_t;


#endif /* NGX_HTTP_RDS_XML_FILTER_MODULE_H */

