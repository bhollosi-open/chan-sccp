/*!
 * \file	sccp_event.h
 * \brief       SCCP Event Header
 * \author      Marcello Ceschia <marcelloceschia [at] users.sourceforge.net>
 * \note	This program is free software and may be modified and distributed under the terms of the GNU Public License.
 *		See the LICENSE file at the top of the source tree.
 * \since       2009-09-02
 */
#pragma once

__BEGIN_C_EXTERN__
/*!
 * \brief SCCP Event Structure
 */
typedef struct sccp_event {
	union {
		struct {
			sccp_line_t *line;									/*!< SCCP Line (required) */
		} lineInstance;											/*!< Event Line Created/Destroyed Structure */
		struct {
			sccp_device_t *device;									/*!< SCCP Device (required) */
		} deviceRegistered;										/*!< Event Device Registered Structure */
		struct {
			sccp_linedevice_t * ld;                                                                 /*!< SCCP device line (required) */
		} deviceAttached;										/*!< Event Device Attached Structure */
		struct {
			sccp_device_t *device;									/*!< SCCP device (required) */
			sccp_linedevice_t * optional_linedevice;                                                /*!< SCCP ld (optional) */
			sccp_feature_type_t featureType;							/*!< what feature is changed (required) */
		} featureChanged;										/*!< Event feature changed Structure */
		struct {
			sccp_line_t * line;                                                                     /*!< SCCP line (required) */
			sccp_device_t *optional_device;								/*!< SCCP device (optional) */
			uint8_t state;										/*!< state (required) */
		} lineStatusChanged;                                                                            /*!< Event feature changed Structure */
#if CS_TEST_FRAMEWORK
		struct {
			uint32_t value;
			char *str;
		} TestEvent;											/*!< Event feature changed Structure */
#endif
	};                                                                                                      /*!< SCCP Event Data Union */
	sccp_event_type_t type;											/*!< Event Type */
} sccp_event_t;													/*!< SCCP Event Structure */

typedef void (*sccp_event_callback_t) (const sccp_event_t * event);

SCCP_API void SCCP_CALL sccp_event_module_start(void);
SCCP_API boolean_t SCCP_CALL sccp_event_subscribe(int eventType, sccp_event_callback_t cb, boolean_t allowAsyncExecution);
SCCP_API sccp_event_t * SCCP_CALL sccp_event_allocate(sccp_event_type_t eventType);
SCCP_API boolean_t SCCP_CALL      _sccp_event_fire(sccp_event_t * event, boolean_t forceSync);
#define sccp_event_fire(_event)     _sccp_event_fire(_event, FALSE)
#define sccp_event_syncFire(_event) _sccp_event_fire(_event, TRUE)
SCCP_API boolean_t SCCP_CALL sccp_event_unsubscribe(int eventType, sccp_event_callback_t cb);
SCCP_API void SCCP_CALL sccp_event_module_stop(void);
__END_C_EXTERN__
// kate: indent-width 8; replace-tabs off; indent-mode cstyle; auto-insert-doxygen on; line-numbers on; tab-indents on; keep-extra-spaces off; auto-brackets off;
