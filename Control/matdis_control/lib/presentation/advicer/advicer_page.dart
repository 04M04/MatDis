import 'package:matdis_control/application/advicer/advicer_bloc.dart';
import 'package:matdis_control/presentation/advicer/error_message.dart';
import 'package:matdis_control/presentation/advicer/widgets/advice_field.dart';
import 'package:matdis_control/presentation/advicer/widgets/custom_button.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

class AdvicerPage extends StatelessWidget {
  const AdvicerPage({super.key});

  @override
  Widget build(BuildContext context) {
    final themeData = Theme.of(context);
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Text(
          "Advicer",
          style: themeData.textTheme.displayLarge,
        ),
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 50),
          child: Column(
            children: [
              Expanded(
                child: Center(
                    child: BlocBuilder<AdvicerBloc, AdvicerState>(
                  bloc: BlocProvider.of<AdvicerBloc>(context),
                  // ..add(AdviceRequestedEvent()), //if you want to preload an advice
                  builder: (context, state) {
                    if (state is AdvicerInitial) {
                      return Text(
                        "Your advice is waiting for you.",
                        style: themeData.textTheme.displayLarge,
                      );
                    } else if (state is AdvicerStateLoading) {
                      return CircularProgressIndicator(
                        color: themeData.colorScheme.secondary,
                      );
                    } else if (state is AdvicerStateLoaded) {
                      return AdviceField(advice: state.advice);
                    } else if (state is AdvicerStateError) {
                      return ErrorMessage(message: state.message);
                    }
                    return const Placeholder();
                  },
                )
                    //ErrorMessage()

                    // AdviceField(advice: "ad")

                    // Text(
                    //   "Your advice is waiting for you.",
                    //   style: themeData.textTheme.displayLarge,
                    // ),
                    ),
              ),
              const SizedBox(
                height: 200,
                child: Center(
                  child: CustomButton(),
                ),
              )
            ],
          ),
        ),
      ),
    );
  }
}
