enum class DistUnit { CENTIMETERS, INCHES, MILLIMITERS, METERS };

class UltrasonicSensor {
private:
  int m_pin;
  int m_pout;
  float m_cache;
  float m_convfact;

  static float getConvFactor(DistUnit unit) {
    float factor = 343 / 2;
    switch (unit) {
    case DistUnit::CENTIMETERS:
      // 10^-6 * 10^2
      factor *= 0.0001;
      break;

    case DistUnit::INCHES:
      // 10^-6 * 10^2 / 2.54
      factor *= 3.937007874015748e-5f;
      break;

    case DistUnit::MILLIMITERS:
      // 10^-6 * 10^3
      factor *= 0.001;
      break;

    case DistUnit::METERS:
      // 10^-6 * 10^6
      factor *= 1;
      break;

    default:
      break;
    }
    return factor;
  }

public:
  UltrasonicSensor() = delete;
  ~UltrasonicSensor() {}

  UltrasonicSensor(int inPin, int outPin) : m_pin(inPin), m_pout(outPin) {
    setConversion(DistUnit::CENTIMETERS);
  }

  float readDistance() {
    // set pin to reset sensor in low
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
    delayMicroseconds(2);

    // set sensor to send pulses
    digitalWrite(m_pin, HIGH);
    delayMicroseconds(10);

    // stop sending pulses and read delay (in us)
    digitalWrite(m_pin, LOW);
    pinMode(m_pout, INPUT);
    m_cache = pulseIn(m_pout, HIGH);
    return m_cache * m_convfact;
  }

  float readCache(DistUnit unit) {
    return m_cache * getConvFactor(unit);
  }

  void setConversion(DistUnit unit) {
    m_convfact = UltrasonicSensor::getConvFactor(unit);
  }
};
