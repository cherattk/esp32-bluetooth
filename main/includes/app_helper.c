/**
 * 
 */

#include "app_helper.h"

const char *bt_status_description(esp_bt_status_t status) {

    switch (status) {
        case ESP_BT_STATUS_SUCCESS:
            return "Success";
            break;
        case ESP_BT_STATUS_FAIL:
            return "Fail";
            break;
        case ESP_BT_STATUS_NOT_READY:
            return "Not Ready";
            break;
        case ESP_BT_STATUS_NOMEM:
            return "No Memory";
            break;
        case ESP_BT_STATUS_BUSY:
            return "Busy";
            break;
        case ESP_BT_STATUS_DONE:
            return "Done";
            break;
        case ESP_BT_STATUS_UNSUPPORTED:
            return "Unsupported";
            break;
        case ESP_BT_STATUS_PARM_INVALID:
            return "Parameter Invalid";
            break;
        case ESP_BT_STATUS_UNHANDLED:
            return "Unhandled";
            break;
        case ESP_BT_STATUS_AUTH_FAILURE:
            return "Authentication Failure";
            break;
        case ESP_BT_STATUS_RMT_DEV_DOWN:
            return "Remote Device Down";
            break;
        case ESP_BT_STATUS_AUTH_REJECTED:
            return "Authentication Rejected";
            break;
        case ESP_BT_STATUS_INVALID_STATIC_RAND_ADDR:
            return "Invalid Static Random Address";
            break;
        case ESP_BT_STATUS_PENDING:
            return "Pending";
            break;
        case ESP_BT_STATUS_UNACCEPT_CONN_INTERVAL:
            return "Unacceptable Connection Interval";
            break;
        case ESP_BT_STATUS_PARAM_OUT_OF_RANGE:
            return "Parameter Out of Range";
            break;
        case ESP_BT_STATUS_TIMEOUT:
            return "Timeout";
            break;
        case ESP_BT_STATUS_PEER_LE_DATA_LEN_UNSUPPORTED:
            return "Peer LE Data Length Unsupported";
            break;
        case ESP_BT_STATUS_CONTROL_LE_DATA_LEN_UNSUPPORTED:
            return "Control LE Data Length Unsupported";
            break;
        case ESP_BT_STATUS_ERR_ILLEGAL_PARAMETER_FMT:
            return "Illegal Parameter Format";
            break;
        case ESP_BT_STATUS_MEMORY_FULL:
            return "Memory Full";
            break;
        case ESP_BT_STATUS_EIR_TOO_LARGE:
            return "EIR Too Large";
            break;
        case ESP_BT_STATUS_HCI_SUCCESS:
            return "HCI Success";
            break;
        case ESP_BT_STATUS_HCI_ILLEGAL_COMMAND:
            return "HCI Illegal Command";
            break;
        case ESP_BT_STATUS_HCI_NO_CONNECTION:
            return "HCI No Connection";
            break;
        case ESP_BT_STATUS_HCI_HW_FAILURE:
            return "HCI Hardware Failure";
            break;
        case ESP_BT_STATUS_HCI_PAGE_TIMEOUT:
            return "HCI Page Timeout";
            break;
        case ESP_BT_STATUS_HCI_AUTH_FAILURE:
            return "HCI Authentication Failure";
            break;
        case ESP_BT_STATUS_HCI_KEY_MISSING:
            return "HCI Key Missing";
            break;
        case ESP_BT_STATUS_HCI_MEMORY_FULL:
            return "HCI Memory Full";
            break;
        case ESP_BT_STATUS_HCI_CONNECTION_TOUT:
            return "HCI Connection Timeout";
            break;
        case ESP_BT_STATUS_HCI_MAX_NUM_OF_CONNECTIONS:
            return "HCI Max Number of Connections";
            break;
        case ESP_BT_STATUS_HCI_MAX_NUM_OF_SCOS:
            return "HCI Max Number of SCOs";
            break;
        case ESP_BT_STATUS_HCI_CONNECTION_EXISTS:
            return "HCI Connection Exists";
            break;
        case ESP_BT_STATUS_HCI_COMMAND_DISALLOWED:
            return "HCI Command Disallowed";
            break;
        case ESP_BT_STATUS_HCI_HOST_REJECT_RESOURCES:
            return "HCI Host Reject Resources";
            break;
        case ESP_BT_STATUS_HCI_HOST_REJECT_SECURITY:
            return "HCI Host Reject Security";
            break;
        case ESP_BT_STATUS_HCI_HOST_REJECT_DEVICE:
            return "HCI Host Reject Device";
            break;
        case ESP_BT_STATUS_HCI_HOST_TIMEOUT:
            return "HCI Host Timeout";
            break;
        case ESP_BT_STATUS_HCI_UNSUPPORTED_VALUE:
            return "HCI Unsupported Value";
            break;
        case ESP_BT_STATUS_HCI_ILLEGAL_PARAMETER_FMT:
            return "HCI Illegal Parameter Format";
            break;
        case ESP_BT_STATUS_HCI_PEER_USER:
            return "HCI Peer User";
            break;
        case ESP_BT_STATUS_HCI_PEER_LOW_RESOURCES:
            return "HCI Peer Low Resources";
            break;
        case ESP_BT_STATUS_HCI_PEER_POWER_OFF:
            return "HCI Peer Power Off";
            break;
        case ESP_BT_STATUS_HCI_CONN_CAUSE_LOCAL_HOST:
            return "HCI Connection Cause Local Host";
            break;
        case ESP_BT_STATUS_HCI_REPEATED_ATTEMPTS:
            return "HCI Repeated Attempts";
            break;
        case ESP_BT_STATUS_HCI_PAIRING_NOT_ALLOWED:
            return "HCI Pairing Not Allowed";
            break;
        case ESP_BT_STATUS_HCI_UNKNOWN_LMP_PDU:
            return "HCI Unknown LMP PDU";
            break;
        case ESP_BT_STATUS_HCI_UNSUPPORTED_REM_FEATURE:
            return "HCI Unsupported Remote Feature";
            break;
        case ESP_BT_STATUS_HCI_SCO_OFFSET_REJECTED:
            return "HCI SCO Offset Rejected";
            break;
        case ESP_BT_STATUS_HCI_SCO_INTERVAL_REJECTED:
            return "HCI SCO Interval Rejected";
            break;
        case ESP_BT_STATUS_HCI_SCO_AIR_MODE:
            return "HCI SCO Air Mode";
            break;
        case ESP_BT_STATUS_HCI_INVALID_LMP_PARAM:
            return "HCI Invalid LMP Parameter";
            break;
        case ESP_BT_STATUS_HCI_UNSPECIFIED:
            return "HCI Unspecified";
            break;
        case ESP_BT_STATUS_HCI_UNSUPPORTED_LMP_PARAMETERS:
            return "HCI Unsupported LMP Parameters";
            break;
        case ESP_BT_STATUS_HCI_ROLE_CHANGE_NOT_ALLOWED:
            return "HCI Role Change Not Allowed";
            break;
        case ESP_BT_STATUS_HCI_LMP_RESPONSE_TIMEOUT:
            return "HCI LMP Response Timeout";
            break;
        case ESP_BT_STATUS_HCI_LMP_ERR_TRANS_COLLISION:
            return "HCI LMP Error Transaction Collision";
            break;
        case ESP_BT_STATUS_HCI_LMP_PDU_NOT_ALLOWED:
            return "HCI LMP PDU Not Allowed";
            break;
        case ESP_BT_STATUS_HCI_ENCRY_MODE_NOT_ACCEPTABLE:
            return "HCI Encryption Mode Not Acceptable";
            break;
        case ESP_BT_STATUS_HCI_UNIT_KEY_USED:
            return "HCI Unit Key Used";
            break;
        case ESP_BT_STATUS_HCI_QOS_NOT_SUPPORTED:
            return "HCI QoS Not Supported";
            break;
        case ESP_BT_STATUS_HCI_INSTANT_PASSED:
            return "HCI Instant Passed";
            break;
        case ESP_BT_STATUS_HCI_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED:
            return "HCI Pairing with Unit Key Not Supported";
            break;
        case ESP_BT_STATUS_HCI_DIFF_TRANSACTION_COLLISION:
            return "HCI Different Transaction Collision";
            break;
        case ESP_BT_STATUS_HCI_UNDEFINED_0x2B:
            return "HCI Undefined (0x2B)";
            break;
        case ESP_BT_STATUS_HCI_QOS_UNACCEPTABLE_PARAM:
            return "HCI QoS Unacceptable Parameter";
            break;
        case ESP_BT_STATUS_HCI_QOS_REJECTED:
            return "HCI QoS Rejected";
            break;
        case ESP_BT_STATUS_HCI_CHAN_CLASSIF_NOT_SUPPORTED:
            return "HCI Channel Classification Not Supported";
            break;
        case ESP_BT_STATUS_HCI_INSUFFCIENT_SECURITY:
            return "HCI Insufficient Security";
            break;
        case ESP_BT_STATUS_HCI_PARAM_OUT_OF_RANGE:
            return "HCI Parameter Out of Range";
            break;
        case ESP_BT_STATUS_HCI_UNDEFINED_0x31:
            return "HCI Undefined (0x31)";
            break;
        case ESP_BT_STATUS_HCI_ROLE_SWITCH_PENDING:
            return "HCI Role Switch Pending";
            break;
        case ESP_BT_STATUS_HCI_UNDEFINED_0x33:
            return "HCI Undefined (0x33)";
            break;
        case ESP_BT_STATUS_HCI_RESERVED_SLOT_VIOLATION:
            return "HCI Reserved Slot Violation";
            break;
        case ESP_BT_STATUS_HCI_ROLE_SWITCH_FAILED:
            return "HCI Role Switch Failed";
            break;
        case ESP_BT_STATUS_HCI_INQ_RSP_DATA_TOO_LARGE:
            return "HCI Inquiry Response Data Too Large";
            break;
        case ESP_BT_STATUS_HCI_SIMPLE_PAIRING_NOT_SUPPORTED:
            return "HCI Simple Pairing Not Supported";
            break;
        case ESP_BT_STATUS_HCI_HOST_BUSY_PAIRING:
            return "HCI Host Busy Pairing";
            break;
        case ESP_BT_STATUS_HCI_REJ_NO_SUITABLE_CHANNEL:
            return "HCI Rejected No Suitable Channel";
            break;
        case ESP_BT_STATUS_HCI_CONTROLLER_BUSY:
            return "HCI Controller Busy";
            break;
        case ESP_BT_STATUS_HCI_UNACCEPT_CONN_INTERVAL:
            return "HCI Unacceptable Connection Interval";
            break;
        case ESP_BT_STATUS_HCI_DIRECTED_ADVERTISING_TIMEOUT:
            return "HCI Directed Advertising Timeout";
            break;
        case ESP_BT_STATUS_HCI_CONN_TOUT_DUE_TO_MIC_FAILURE:
            return "HCI Connection Timeout Due to MIC Failure";
            break;
        case ESP_BT_STATUS_HCI_CONN_FAILED_ESTABLISHMENT:
            return "HCI Connection Failed Establishment";
            break;
        case ESP_BT_STATUS_HCI_MAC_CONNECTION_FAILED:
            return "HCI MAC Connection Failed";
            break;
        default:
            return "Unknown status";
            break;
    }
}