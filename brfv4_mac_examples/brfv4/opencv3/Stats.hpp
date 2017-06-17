#ifndef __brf__Stats_hpp
#define __brf__Stats_hpp

namespace brf {

	class Stats {

		private: const int WIDTH;
		private: const int HEIGHT;
		private: const int GRAPH_OFFSET;

		private: cv::Mat _frame;
		private: cv::Mat _graph;

		private: double _prevTime;
		private: double _fps;

		public: Stats() :
				WIDTH(65 + 25),
				HEIGHT(50),
				GRAPH_OFFSET(20),

				_frame(HEIGHT, WIDTH, CV_8UC4, cv::Scalar(33, 0, 0, 255)),
				_graph(HEIGHT - GRAPH_OFFSET, WIDTH, CV_8UC4, cv::Scalar(33, 0, 0, 255)),
				_prevTime(0.0),
				_fps(0.0) {
		}

		public: void update() {
			_fps += 1.0;

			int64 ticks = cv::getTickCount();
			double freq = cv::getTickFrequency();
			double time = (double)ticks / freq;

			if(time - 1.0 > _prevTime ) {
				double timeDiff = time - _prevTime;

				_prevTime = time;

				_graph.colRange(1, _graph.cols).rowRange(0, _graph.rows).copyTo(
					_graph.colRange(0, _graph.cols - 1).rowRange(0, _graph.rows)
				);

				cv::rectangle(_graph, cv::Rect(_graph.cols - 1, 0, 1, _graph.rows),
					cv::Scalar(33, 0, 0, 255), cv::FILLED);

				int baseFPS = 60;
				double fps = round(_fps / timeDiff);
				double percent = (double)fps / (double)baseFPS;
				double rowPercent = 1.0 - percent;

				if(rowPercent < 0.0) rowPercent = 0.0;
				if(rowPercent > 1.0) rowPercent = 1.0;

				int row = rowPercent * (double)_graph.rows;

				cv::rectangle(_graph, cv::Rect(_graph.cols - 1, row, 1, 1),
					cv::Scalar(0, 0, 255, 255), cv::FILLED);

				cv::rectangle(_frame, cv::Rect(0, 0, _frame.cols, _frame.rows), cv::Scalar(33, 0, 0, 255), cv::FILLED);
				cv::putText(_frame, "fps: " + brf::to_string(round(fps)), cv::Point(1, 13), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255, 255), 1, 0, false);

				_fps = 0;
			}
		}

		public: void render(cv::Mat& frame) {
			if(_frame.type() == CV_8UC3 && frame.type() == CV_8UC4) {
				cv::cvtColor(_frame, _frame, cv::COLOR_BGR2BGRA);
				cv::cvtColor(_graph, _graph, cv::COLOR_BGR2BGRA);
			} else if(_frame.type() == CV_8UC4 && frame.type() == CV_8UC3) {
				cv::cvtColor(_frame, _frame, cv::COLOR_BGRA2BGR);
				cv::cvtColor(_graph, _graph, cv::COLOR_BGRA2BGR);
			}

			unsigned int _yOffset = 0;

			_graph.copyTo(_frame.colRange(0, _graph.cols).rowRange(GRAPH_OFFSET, _graph.rows  + GRAPH_OFFSET));
			_frame.copyTo( frame.colRange(frame.cols - _frame.cols, frame.cols).rowRange(0+_yOffset, _frame.rows+_yOffset));
		}
	};
};

#endif /* __brf__Stats_hpp */
