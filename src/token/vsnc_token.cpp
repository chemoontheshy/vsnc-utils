#include "vsnc_token.h"
#include "vsnc_token_impl.h"

vsnc::utils::InstanceTUPtr::InstanceTUPtr() :m_pTokenUtils(TokenUtilsPtr(new TokenUtilsIMPL()))
{
}
