import 'package:matdis_control/application/advicer/advicer_bloc.dart';
import 'package:matdis_control/domain/repositories/advicer_repository.dart';
import 'package:matdis_control/domain/usecases/advicer_usecases.dart';
import 'package:matdis_control/infrastructure/datasources/advicer_remote_datasource.dart';
import 'package:matdis_control/infrastructure/repositories/advicer_repository_implementation.dart';
import 'package:get_it/get_it.dart';
import 'package:http/http.dart';

final sl = GetIt.I;

Future<void> init() async {
  //!Blocs
  sl.registerFactory(() => AdvicerBloc(advicerUsecases: sl()));
  //!Usecases
  sl.registerLazySingleton(() => AdvicerUsecases(adviceRepository: sl()));
  //!Repositories
  sl.registerLazySingleton<AdvicerRepository>(
      () => AdvicerRepositoryImplementation(adviceRemoteDatasource: sl()));
  //!Datasource
  sl.registerLazySingleton<AdviceRemoteDatasource>(
      () => AdviceRemoteDatasourceImplementation(client: sl()));
  //!EXTERN
  sl.registerLazySingleton(() => Client());
}
