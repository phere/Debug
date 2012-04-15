/*
 *  Channel.h
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import <string>
#import <boost/noncopyable.hpp>

namespace phere {
	namespace debug {
		class Channel : protected boost::noncopyable {
		public:
			enum EMessageLevel {
				eTrace,
				eMessage,
				eWarning,
				eError
			};

			virtual ~Channel();

			std::string GetName() const;
			
			EMessageLevel GetThreshold() const;
			void SetThreshold(EMessageLevel eThreshold);

			void Message(EMessageLevel eLevel, const char* pszMessage) const;
			void Message(EMessageLevel eLevel, const std::string& strMessage) const;

		protected:
			Channel(const std::string& strName);
			virtual void ShowMessage(const std::string& strMessage, EMessageLevel eLevel) const = 0;
			
		private:
			EMessageLevel m_eThreshold;
			std::string m_strName;
		};
	}
}
