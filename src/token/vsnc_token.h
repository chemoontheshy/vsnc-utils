#ifndef __VNSC_UTILS_TOKEN_H__
#define __VNSC_UTILS_TOKEN_H__
#include <iostream>
#include "../vsnc_utils.h"

namespace vsnc
{
	namespace utils
	{
		/**
		 * @brief ����token��������ʱֻ֧���û����ͳ�ʱʱ��
		*/
		//struct TokenParam
		//{
		//	/**
		//	 * @brief �û���
		//	*/
		//	std::string User;
		//	/**
		//	 * @brief ��ʱʱ��
		//	*/
		//	size_t      Expires;
		//	/**
		//	 * @brief �Σ�
		//	*/
		//	std::string Token;
		//};

		/**
		 * @brief Token������
		*/
		class TokenUtils
		{
		public:
			/*
			*  Ĭ����������
			*/
			~TokenUtils() = default;

			/**
			 * @brief token������
			 * @param user ǩ���û�
			 * @param expires ��ʱʱ��
			 * @return ����token
			*/
			virtual const std::string CreateToken(const std::string& __VSNC_IN user, const size_t __VSNC_IN expires) noexcept = 0;


			/**
			 * @brief ��֤token
			 * @param user ǩ���û�
			 * @param token token
			 * @return 0:��֤�ɹ���1:token���ڡ�2���Ƿ�token
			*/
			virtual const size_t VerifyToken(const std::string& __VSNC_IN user, const std::string& __VSNC_IN token) noexcept = 0;
		};

		/**
		 * @brief ʹ�ñ���
		*/
		using   TokenUtilsPtr = std::shared_ptr<TokenUtils>;

		/**
		 * @brief ʵ����Token������,����ʵ�ֵ���ģʽ
		*/
		class InstanceTUPtr
		{
		public:
			/**
			 * @brief ���캯��
			*/
			InstanceTUPtr();

			/**
			 * @brief ��ȡToken������ָ��
			 * @return Token������ָ��
			*/
			TokenUtilsPtr GetTokenUtilsPtr() { return m_pTokenUtils; }
		private:
			/**
			 * @brief Token������ָ��
			*/
			TokenUtilsPtr m_pTokenUtils;
		};

		/**
		 * @brief ʵ����Token�����൥��
		*/
		typedef vsnc::utils::SingletonPtr<InstanceTUPtr> SingleTUPtr;
	}
}

#endif // !__VNSC_UTILS_TOKEN_H__

