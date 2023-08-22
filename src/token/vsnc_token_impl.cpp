#include "vsnc_token_impl.h"
#include "jwt-cpp/jwt.h"
namespace vsnc
{
	namespace utils
	{
		static const char* VSNC_PRIVATE_KEY = "b42273db9e6c1f9911b038c778af4377";
	}
}

const std::string vsnc::utils::TokenUtilsIMPL::CreateToken(const std::string& __VSNC_IN user, const size_t __VSNC_IN expires) noexcept
{
	auto token = jwt::create()
		.set_issuer(user)
		.set_issued_at(std::chrono::system_clock::now())
		.set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{ expires })
		.sign(jwt::algorithm::hs256{ VSNC_PRIVATE_KEY });
	return token;
}

const size_t vsnc::utils::TokenUtilsIMPL::VerifyToken(const std::string& __VSNC_IN user, const std::string& __VSNC_IN token) noexcept
{
	auto verifier = jwt::verify()
		.allow_algorithm(jwt::algorithm::hs256{ VSNC_PRIVATE_KEY })
		.with_issuer(user)
		.expires_at_leeway(10);
	auto decoded = jwt::decode(token);
	size_t ret = 0;
	try {
		verifier.verify(decoded);
		ret = 0;
		std::cout << "Success!" << std::endl;
	}
	catch (const std::exception& ex) {
		std::string strError = ex.what();
		std::cout << strError << std::endl;
		if (strError.find("expired") != std::string::npos)
		{
			ret = 1;
		}
		else
		{
			ret = 2;
		}
	}
	return ret;
}
