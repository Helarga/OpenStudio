/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PrjSubobjectsImpl.hpp"
#include "../../utilities/core/StringHelpers.hpp"
namespace openstudio {
namespace contam {
  namespace detail {

    void WeatherDataImpl::setDefaults() {
      m_Tambt = PRJFLOAT("0.0");
      m_barpres = PRJFLOAT("0.0");
      m_windspd = PRJFLOAT("0.0");
      m_winddir = PRJFLOAT("0.0");
      m_relhum = PRJFLOAT("0.0");
      m_daytyp = 0;
      m_uTa = 0;
      m_ubP = 0;
      m_uws = 0;
      m_uwd = 0;
    }

    WeatherDataImpl::WeatherDataImpl() {
      setDefaults();
    }

    WeatherDataImpl::WeatherDataImpl(std::string Tambt, std::string barpres, std::string windspd, std::string winddir, std::string relhum, int daytyp,
                                     int uTa, int ubP, int uws, int uwd) {
      setDefaults();
      setTambt(Tambt);
      setBarpres(barpres);
      setWindspd(windspd);
      setWinddir(winddir);
      setRelhum(relhum);
      setDaytyp(daytyp);
      setUTa(uTa);
      setUbP(ubP);
      setUws(uws);
      setUwd(uwd);
    }

    WeatherDataImpl::WeatherDataImpl(double Tambt, double barpres, double windspd, double winddir, double relhum, int daytyp, int uTa, int ubP,
                                     int uws, int uwd) {
      setDefaults();
      setTambt(Tambt);
      setBarpres(barpres);
      setWindspd(windspd);
      setWinddir(winddir);
      setRelhum(relhum);
      setDaytyp(daytyp);
      setUTa(uTa);
      setUbP(ubP);
      setUws(uws);
      setUwd(uwd);
    }

    void WeatherDataImpl::read(Reader& input) {
      setTambt(input.readNumber<std::string>());
      setBarpres(input.readNumber<std::string>());
      setWindspd(input.readNumber<std::string>());
      setWinddir(input.readNumber<std::string>());
      setRelhum(input.readNumber<std::string>());
      setDaytyp(input.read<int>());
      setUTa(input.read<int>());
      setUbP(input.read<int>());
      setUws(input.read<int>());
      setUwd(input.read<int>());
    }

    std::string WeatherDataImpl::write() {
      std::string string;
      string += ANY_TO_STR(m_Tambt) + ' ' + ANY_TO_STR(m_barpres) + ' ' + ANY_TO_STR(m_windspd) + ' ' + ANY_TO_STR(m_winddir) + ' '
                + ANY_TO_STR(m_relhum) + ' ' + ANY_TO_STR(m_daytyp) + ' ' + ANY_TO_STR(m_uTa) + ' ' + ANY_TO_STR(m_ubP) + ' ' + ANY_TO_STR(m_uws)
                + ' ' + ANY_TO_STR(m_uwd) + '\n';
      return string;
    }

    double WeatherDataImpl::Tambt() const {
      return openstudio::string_conversions::to<double>(m_Tambt);
    }

    bool WeatherDataImpl::setTambt(const double Tambt) {
      m_Tambt = openstudio::string_conversions::number(Tambt);
      return true;
    }

    bool WeatherDataImpl::setTambt(const std::string& Tambt) {
      return assign_if_valid<double>(Tambt, m_Tambt);
    }

    double WeatherDataImpl::barpres() const {
      return openstudio::string_conversions::to<double>(m_barpres);
    }

    bool WeatherDataImpl::setBarpres(const double barpres) {
      m_barpres = openstudio::string_conversions::number(barpres);
      return true;
    }

    bool WeatherDataImpl::setBarpres(const std::string& barpres) {
      return assign_if_valid<double>(barpres, m_barpres);
    }

    double WeatherDataImpl::windspd() const {
      return openstudio::string_conversions::to<double>(m_windspd);
    }

    bool WeatherDataImpl::setWindspd(const double windspd) {
      m_windspd = openstudio::string_conversions::number(windspd);
      return true;
    }

    bool WeatherDataImpl::setWindspd(const std::string& windspd) {
      return assign_if_valid<double>(windspd, m_windspd);
    }

    double WeatherDataImpl::winddir() const {
      return openstudio::string_conversions::to<double>(m_winddir);
    }

    bool WeatherDataImpl::setWinddir(const double winddir) {
      m_winddir = openstudio::string_conversions::number(winddir);
      return true;
    }

    bool WeatherDataImpl::setWinddir(const std::string& winddir) {
      return assign_if_valid<double>(winddir, m_winddir);
    }

    double WeatherDataImpl::relhum() const {
      return openstudio::string_conversions::to<double>(m_relhum);
    }

    bool WeatherDataImpl::setRelhum(const double relhum) {
      m_relhum = openstudio::string_conversions::number(relhum);
      return true;
    }

    bool WeatherDataImpl::setRelhum(const std::string& relhum) {
      return assign_if_valid<double>(relhum, m_relhum);
    }

    int WeatherDataImpl::daytyp() const {
      return m_daytyp;
    }

    void WeatherDataImpl::setDaytyp(const int daytyp) {
      m_daytyp = daytyp;
    }

    int WeatherDataImpl::uTa() const {
      return m_uTa;
    }

    void WeatherDataImpl::setUTa(const int uTa) {
      m_uTa = uTa;
    }

    int WeatherDataImpl::ubP() const {
      return m_ubP;
    }

    void WeatherDataImpl::setUbP(const int ubP) {
      m_ubP = ubP;
    }

    int WeatherDataImpl::uws() const {
      return m_uws;
    }

    void WeatherDataImpl::setUws(const int uws) {
      m_uws = uws;
    }

    int WeatherDataImpl::uwd() const {
      return m_uwd;
    }

    void WeatherDataImpl::setUwd(const int uwd) {
      m_uwd = uwd;
    }

    void IconImpl::setDefaults() {
      m_icon = 0;
      m_col = 0;
      m_row = 0;
      m_nr = 0;
    }

    IconImpl::IconImpl() {
      setDefaults();
    }

    IconImpl::IconImpl(int icon, int col, int row, int nr) {
      setDefaults();
      setIcon(icon);
      setCol(col);
      setRow(row);
      setNr(nr);
    }

    void IconImpl::read(Reader& input) {
      setIcon(input.read<int>());
      setCol(input.read<int>());
      setRow(input.read<int>());
      setNr(input.read<int>());
    }

    std::string IconImpl::write() {
      std::string string;
      string += ANY_TO_STR(m_icon) + ' ' + ANY_TO_STR(m_col) + ' ' + ANY_TO_STR(m_row) + ' ' + ANY_TO_STR(m_nr) + '\n';
      return string;
    }

    int IconImpl::icon() const {
      return m_icon;
    }

    void IconImpl::setIcon(const int icon) {
      m_icon = icon;
    }

    int IconImpl::col() const {
      return m_col;
    }

    void IconImpl::setCol(const int col) {
      m_col = col;
    }

    int IconImpl::row() const {
      return m_row;
    }

    void IconImpl::setRow(const int row) {
      m_row = row;
    }

    int IconImpl::nr() const {
      return m_nr;
    }

    void IconImpl::setNr(const int nr) {
      m_nr = nr;
    }

    bool IconImpl::isWall() {
      return (m_icon >= WL_EW) && (m_icon <= WL_NESW);
    }

  }  // namespace detail
}  // namespace contam
}  // namespace openstudio
